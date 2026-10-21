#include "DsoCoreTaskSampleBuffer.h"
#include "MdmaCopy.h"

//----------------------------------------------------------------------------------------------------------//
#define DSO_CORE_TASK_SET_MEMORY_STATE(state)														(DsoBufferState = state)
#define DSO_CORE_TASK_GET_MEMORY_STATE																(DsoBufferState)
//----------------------------------------------------------------------------------------------------------//
__attribute__((section(".dma_buffer")))
static uint16_t sample[DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH];
static uint32_t writeStartIndex;
static uint32_t readStartIndex;
static DsoBufferRange DsoBufferState;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreTaskCaculaterWriteIndex(uint32_t size);
//----------------------------------------------------------------------------------------------------------//
void DsoCoreTaskSampleBufferInit(MDMA_HandleTypeDef *_mdma){
	MdmaCopyInit(_mdma);
}

void DsoCoreTaskBufferReset(){
	writeStartIndex = 0;
	readStartIndex = 0;
	DSO_CORE_TASK_SET_MEMORY_STATE(DSO_SAMPLE_BUFFER_PARTIAL);
}


void DsoCoreTaskCaculaterWriteIndex(uint32_t size){
	if(writeStartIndex + size >= DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH){
		DSO_CORE_TASK_SET_MEMORY_STATE(DSO_SAMPLE_BUFFER_FULL);
		writeStartIndex = 0;
	} else
		writeStartIndex += size;
}

uint32_t DsoCoreTaskCaculaterReadIndex(uint32_t size, DsoBufferShift direction, uint32_t shiftFactor){
	int index = readStartIndex +  size * (direction) * shiftFactor;
	if(DSO_CORE_TASK_GET_MEMORY_STATE == DSO_SAMPLE_BUFFER_PARTIAL && (index < 0)){
		return 0;
	} else if(DSO_CORE_TASK_GET_MEMORY_STATE == DSO_SAMPLE_BUFFER_PARTIAL && (index >= DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH)){
		return (DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH - 1);
	} else{
		return readStartIndex;
	}

}

void DsoCoreTaskPushSample(uint16_t *ptr, uint32_t size){
	MdmaContinuousMemory((uint32_t*)ptr, (uint32_t*)sample + writeStartIndex, size, 0);
	DsoCoreTaskCaculaterWriteIndex(size);
}

uint32_t DsoCoreTaskPopSample(uint16_t **ptr, uint32_t size){
	/*
	uint32_t availableBufferSize = 0;
	*ptr = writeStartIndex;
	DSO_CORE_TASK_CACULATED_INDEX(&readStartIndex, size);
	*/
	return 0;
}
