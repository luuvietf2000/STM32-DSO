#ifndef TASK_ST7789DRIVERTASK_INC_ST7789DMAMEMORY_H_
#define TASK_ST7789DRIVERTASK_INC_ST7789DMAMEMORY_H_

#include "St7789Conf.h"
#include "FreeRTOS.h"
#include <stdint.h>
//------------------------------------------------------------------------------------------------//
#define ST7789_DMA_MEMORY_SIZE_EMPTY															0
#define ST7789_DMA_MEMORY_ONE_INDEX																1
#define ST7789_DMA_MEMORY_FREE_BLOCK_INDEX_IN_POOL												0
#define ST7789_DMA_MEMORY_NOT_USED_BLOCK_INDEX_IN_POOL											1
//------------------------------------------------------------------------------------------------//
typedef enum{
	ST7789_TASK_SLEEP,
	ST7789_TASK_WAKE
} St7789TaskStatus;
//------------------------------------------------------------------------------------------------//
typedef struct St7789DmaMemoryBlock{
	uint32_t start;
	uint32_t end;
	struct St7789DmaMemoryBlock *per;
	struct St7789DmaMemoryBlock *next;
} St7789DmaMemoryBlock;
//------------------------------------------------------------------------------------------------//
void St7789DmaMemoryFree(uint32_t start, uint32_t size);
void St7789DmaMemoryInit();
uint8_t* St7789DmaMemoryAlloc(uint32_t preferredSize, uint32_t fallbackSize, uint32_t *index, uint32_t *size);

#endif /* TASK_ST7789DRIVERTASK_INC_ST7789DMAMEMORY_H_ */
