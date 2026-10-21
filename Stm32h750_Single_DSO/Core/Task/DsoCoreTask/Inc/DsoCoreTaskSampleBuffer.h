#ifndef TASK_DSOCORETASK_INC_DSOCORETASKSAMPLEBUFFER_H_
#define TASK_DSOCORETASK_INC_DSOCORETASKSAMPLEBUFFER_H_

#include "DsoCoreTaskConf.h"
#include "stm32h7xx_hal.h"
//----------------------------------------------------------------------------------------------------------//
typedef enum{
    DSO_SAMPLE_BUFFER_PARTIAL,
    DSO_SAMPLE_BUFFER_FULL
} DsoBufferRange;

typedef enum{
	DSO_SAMPLE_BUFFER_SHIFT_LEFT 												= -1,
	DSO_SAMPLE_BUFFER_SHIFT_RIGHT												=  1
} DsoBufferShift;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreTaskSampleBufferInit(MDMA_HandleTypeDef *_mdma);
void DsoCoreTaskBufferReset();
void DsoCoreTaskPushSample(uint16_t *ptr, uint32_t size);
#endif /* TASK_DSOCORETASK_INC_DSOCORETASKSAMPLEBUFFER_H_ */
