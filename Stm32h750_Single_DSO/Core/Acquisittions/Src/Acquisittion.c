#include "Acquisittion.h"
#include "stm32h7xx_hal.h"

#include "AcquisittionConf.h"
//---------------------------------------------------------------------------//
#define ACQUISITTION_PARTITION_COUNT									2
#define ACQUISITTION_PARTITION_SIZE										(ACQUISITTION_BUFFER_LENGTH / ACQUISITTION_PARTITION_COUNT)
#define ACQUISITTION_FIRST_HALT_INDEX									0
#define ACQUISITTION_SECOND_HALT_INDEX									(ACQUISITTION_FIRST_HALT_INDEX + ACQUISITTION_PARTITION_SIZE)
//---------------------------------------------------------------------------//
static ADC_HandleTypeDef *adc;

__attribute__((section(".dma_buffer")))
static uint16_t sample[ACQUISITTION_BUFFER_LENGTH];

static void (*acquisittionHaltTransferFinishPtr)(uint16_t *ptr, uint16_t size) = NULL;
//---------------------------------------------------------------------------//

void AcquisittionInit(ADC_HandleTypeDef *_adc){
	adc = _adc;
}

void AcquisittionSetupCallback(void (*functionCallback)(uint16_t *ptr, uint16_t size)){
	acquisittionHaltTransferFinishPtr = functionCallback;
}

HAL_StatusTypeDef AcquisittionStart(){
	HAL_StatusTypeDef result = HAL_ADC_Start_DMA(adc, (uint32_t*)sample, ACQUISITTION_BUFFER_LENGTH);
	return result;
}

void AcquisittionStop(){
	HAL_ADC_Stop_DMA(adc);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
    if(hadc == adc){
    	acquisittionHaltTransferFinishPtr(sample + ACQUISITTION_SECOND_HALT_INDEX, ACQUISITTION_PARTITION_SIZE);
    }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc){
	if(hadc == adc){
		acquisittionHaltTransferFinishPtr(sample + ACQUISITTION_FIRST_HALT_INDEX, ACQUISITTION_PARTITION_SIZE);
	}
}
