#include "MdmaCopy.h"
#include "semphr.h"
#include "FreeRTOS.h"

//----------------------------------------------------------------------------------------------------------//
static MDMA_HandleTypeDef *mdma;
static StaticSemaphore_t semaphoreBuffer;
static SemaphoreHandle_t semaphore;
//----------------------------------------------------------------------------------------------------------//
void MdmaCopyTransferComple(MDMA_HandleTypeDef *hmdma);
//----------------------------------------------------------------------------------------------------------//
void MdmaCopyInit(MDMA_HandleTypeDef *_mdma){
	mdma = _mdma;
	HAL_MDMA_RegisterCallback(mdma, HAL_MDMA_XFER_CPLT_CB_ID, MdmaCopyTransferComple);
	semaphore = xSemaphoreCreateBinaryStatic(&semaphoreBuffer);
}

HAL_StatusTypeDef MdmaContinuousMemory(uint32_t *src, uint32_t *des, uint32_t blockLengthBuffer, uint32_t blockCount){
	HAL_StatusTypeDef result = HAL_MDMA_Start_IT(mdma, (uint32_t) src, (uint32_t) des, blockLengthBuffer, blockCount);
	if(result == HAL_OK)
		xSemaphoreTake(semaphore, MDMACOPY_TIME_FOREVER);
	return result;
}

void MdmaCopyTransferComple(MDMA_HandleTypeDef *hmdma){
	if(hmdma == mdma){
		BaseType_t priority = pdFALSE;
		xSemaphoreGiveFromISR(semaphore, &priority);
		portYIELD_FROM_ISR(priority);
	}
}
