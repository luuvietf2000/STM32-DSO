#ifndef TASK_DSOCORETASK_INC_DSO_CORE_ACQUISITTION_BUFFER_H_
#define TASK_DSOCORETASK_INC_DSO_CORE_ACQUISITTION_BUFFER_H_

#include "stdint.h"
#include "GraphicsWaveformWidget.h"
#include "DsoCoreTaskConf.h"
//---------------------------------------------------------------------------//
typedef enum{
	DSO_CORE_TASK_ACQUISITTION_MODE_SCROLL
} DsoCoreAcquisittionMode;

typedef enum{
	DSO_CORE_TASK_ACQUISITTION_BUFFER_MEMORY_EMPTY,
	DSO_CORE_TASK_ACQUISITTION_BUFFER_MEMORY_AVAILABLE
} DsoCoreAcquisittionBufferState;
//---------------------------------------------------------------------------//
uint16_t *DsoCoreGetAcquisitionBufferNextWritePtr(uint32_t size);
uint16_t *DsoCoreGetAcquisitionBufferPerWritePtr(uint32_t size);
void DsoCoreProcessAcquisitionBufferChunk(GraphicsPoint *ptr, float *voltageMax, float *voltageMin);
#endif /* TASK_DSOCORETASK_INC_DSO_CORE_ACQUISITTION_BUFFER_H_ */
