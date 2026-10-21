#ifndef MDMACOPY_INC_MDMACOPY_H_
#define MDMACOPY_INC_MDMACOPY_H_

#include "stm32h7xx_hal.h"
#include "FreeRTOS.h"
//----------------------------------------------------------------------------------------------------------//
#define MDMACOPY_TIME_FOREVER																	portMAX_DELAY
#define MDMACOPY_TIME_NONE																		0
//----------------------------------------------------------------------------------------------------------//
void MdmaCopyInit(MDMA_HandleTypeDef *_mdma);
HAL_StatusTypeDef MdmaContinuousMemory(uint32_t *src, uint32_t *des, uint32_t blockLengthBuffer, uint32_t blockCount);

#endif /* MDMACOPY_INC_MDMACOPY_H_ */
