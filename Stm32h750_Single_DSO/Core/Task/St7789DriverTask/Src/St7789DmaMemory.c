#include "St7789DmaMemory.h"
#include "semphr.h"
//------------------------------------------------------------------------------------------------//
#define ST7789_DMA_SIZE_AVAILABLE
#define ST7789_DMA_MEMORY_IS_IN_RANGE(value, start, end)							(end > value && value > start)
//------------------------------------------------------------------------------------------------//
static void St7789DmaMemoryPushBlockNotUsed(St7789DmaMemoryBlock *block);
static void St7789DmaMemoryBlockNotUsedListInit(uint32_t index);
static void St7789DmaMemoryBlockFreeListInit(uint32_t index);
static St7789DmaMemoryBlock* St7789DmaMemoryGetBlockNotUsed();
static uint32_t St7789DmaMemoryAllocBlock(St7789DmaMemoryBlock *block, uint32_t allocationSize);
static void St7789DmaMemoryMergeBlock(uint32_t start, uint32_t end);
static uint32_t St7789DmaMemoryGetSizeAvailable(St7789DmaMemoryBlock ** block, uint32_t preferredSize, uint32_t fallbackSize);
static void St7789DmaMemoryTaskWake();
static void St7789DmaMemorySetBlock(St7789DmaMemoryBlock *current, uint32_t start, uint32_t end, St7789DmaMemoryBlock *pre, St7789DmaMemoryBlock *next);
//------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------//
__attribute__((section(".dma_buffer")))
static uint8_t dmaMemory[ST7789_DMA_MEMORY];
static St7789DmaMemoryBlock poolBlock[ST7789_MSG_POOL_ITEM_LENGTH];
static St7789DmaMemoryBlock *headBlockFree;
static St7789DmaMemoryBlock *headBlockNotUsed;
static uint32_t fallback;
//------------------------------------------------------------------------//
static StaticSemaphore_t mutexBuffer;
static SemaphoreHandle_t mutex;
static St7789TaskStatus taskSleepStatus;
static StaticSemaphore_t semaphoreBuffer;
static SemaphoreHandle_t semaphore;

//------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------//

static void St7789DmaMemoryTaskWake(uint32_t size){
	if(size < fallback)
		return;
	if(taskSleepStatus == ST7789_TASK_SLEEP){
		taskSleepStatus = ST7789_TASK_WAKE;
		xSemaphoreGive(semaphore);
	}
}
static void St7789DmaMemorySetBlock(St7789DmaMemoryBlock *current, uint32_t start, uint32_t end, St7789DmaMemoryBlock *pre, St7789DmaMemoryBlock *next){
	current->per = pre;
	current->next = next;
	current->start = start;
	current->end = end;
}
static void St7789DmaMemoryBlockFreeListInit(uint32_t index){
	headBlockFree = poolBlock;
	St7789DmaMemorySetBlock(
		poolBlock,
		0,
		ST7789_DMA_MEMORY - ST7789_DMA_MEMORY_ONE_INDEX,
		NULL,
		NULL
	);
}
static void St7789DmaMemoryBlockNotUsedListInit(uint32_t index){
	for(uint32_t i = index; i < ST7789_MSG_POOL_ITEM_LENGTH; i++)
		St7789DmaMemoryPushBlockNotUsed(poolBlock + i);
}
void St7789DmaMemoryInit(){
	mutex = xSemaphoreCreateMutexStatic(&mutexBuffer);
	semaphore = xSemaphoreCreateBinaryStatic(&semaphoreBuffer);
	taskSleepStatus = ST7789_TASK_WAKE;
	St7789DmaMemoryBlockFreeListInit(ST7789_DMA_MEMORY_FREE_BLOCK_INDEX_IN_POOL);
	St7789DmaMemoryBlockNotUsedListInit(ST7789_DMA_MEMORY_FREE_BLOCK_INDEX_IN_POOL);
}

void St7789DmaMemoryFree(uint32_t start, uint32_t size){
	xSemaphoreTake(mutex, ST7789_TIMEOUT_FOREVER);
	St7789DmaMemoryMergeBlock(start, start + size - ST7789_DMA_MEMORY_ONE_INDEX);
	xSemaphoreGive(mutex);
}
static void St7789DmaMemoryMergeBlock(uint32_t start, uint32_t end){
	St7789DmaMemoryBlock *current = headBlockFree;
	St7789DmaMemoryBlock *pre = NULL;
	while(current != NULL && current->start < start){
		if(current->end + 1 == start){
			current->end = end;
			St7789DmaMemoryBlock *next = current->next;
			if(next != NULL && end + 1 == next->start){
				current->end = next->end;
				current->next = next->next;
				if(current->next != NULL)
					current->next->per = current;
				St7789DmaMemoryPushBlockNotUsed(next);
			}
			St7789DmaMemoryTaskWake(current->end - current->start + ST7789_DMA_MEMORY_ONE_INDEX);
			return;
		}
		pre = current;
		current = current->next;
	}
	if(current != NULL && current->start == end + 1){
		current->start = start;
		St7789DmaMemoryTaskWake(current->end - current->start + ST7789_DMA_MEMORY_ONE_INDEX);
		return;
	}
	St7789DmaMemoryBlock *block = St7789DmaMemoryGetBlockNotUsed();
	block->start = start;
	block->end = end;

	if(headBlockFree == NULL){
		headBlockFree = block;
	    block->per = NULL;
	    block->next = NULL;
	} else{
		if(pre != NULL)
			pre->next = block;
		else
			headBlockFree = block;
		block->per = pre;
		block->next = current;

		if(current != NULL)
			current->per = block;
	}
	St7789DmaMemoryTaskWake(block->end - block->start + ST7789_DMA_MEMORY_ONE_INDEX);
}

static void St7789DmaMemoryPushBlockNotUsed(St7789DmaMemoryBlock *block){
	block->next = headBlockNotUsed;
	headBlockNotUsed = block;
}

static St7789DmaMemoryBlock* St7789DmaMemoryGetBlockNotUsed(){
	St7789DmaMemoryBlock* block = headBlockNotUsed;
	headBlockNotUsed = block->next;
	return block;
}

static uint32_t St7789DmaMemoryAllocBlock(St7789DmaMemoryBlock *block, uint32_t allocationSize){
	uint32_t size = block->end - block->start + ST7789_DMA_MEMORY_ONE_INDEX;
	uint32_t index = block->start;
	if(size > allocationSize){
		block->start += allocationSize;
		return index;
	} else{
        St7789DmaMemoryBlock *pre = block->per;
        St7789DmaMemoryBlock *next = block->next;
        if (pre != NULL)
			pre->next = next;
		else
			headBlockFree = next;

		if (next != NULL)
			next->per = pre;
		St7789DmaMemoryPushBlockNotUsed(block);

	}
	return index;
}

static uint32_t St7789DmaMemoryGetSizeAvailable(St7789DmaMemoryBlock ** block, uint32_t preferredSize, uint32_t fallbackSize){
	uint32_t size;
	uint32_t allocationSize = UINT32_MAX;
	St7789DmaMemoryBlock *current = headBlockFree;
	while(current != NULL){
		size = current->end - current->start + ST7789_DMA_MEMORY_ONE_INDEX;
		if(preferredSize == size){
			*block = current;
			return size;
		} else if(size > preferredSize && (size < allocationSize || allocationSize < preferredSize)){
			allocationSize = preferredSize;
			*block = current;
		} else if(
				(UINT32_MAX == allocationSize && size >= fallbackSize)|| (
						ST7789_DMA_MEMORY_IS_IN_RANGE(size, fallbackSize, preferredSize)
						&& ST7789_DMA_MEMORY_IS_IN_RANGE(allocationSize, fallbackSize, preferredSize)
						&& allocationSize > size
				)
			){
			allocationSize = fallbackSize;
			*block = current;
		}
		current = current->next;
	}
	return allocationSize == UINT32_MAX ? ST7789_DMA_MEMORY_SIZE_EMPTY : allocationSize;
}

uint8_t* St7789DmaMemoryAlloc(uint32_t preferredSize, uint32_t fallbackSize, uint32_t *index, uint32_t *size){
	St7789DmaMemoryBlock *block;
	*size = 0;
	while(*size == 0){
		xSemaphoreTake(mutex, ST7789_TIMEOUT_FOREVER);
		*size = St7789DmaMemoryGetSizeAvailable(&block, preferredSize, fallbackSize);
		if(*size != 0)
			*index = St7789DmaMemoryAllocBlock(block, *size);
		xSemaphoreGive(mutex);
		if(*size == 0){
			fallback = fallbackSize;
			taskSleepStatus = ST7789_TASK_SLEEP;
			xSemaphoreTake(semaphore, ST7789_TIMEOUT_FOREVER);
		}

	}
	return dmaMemory + *index;
}
