#include "Acquisittion.h"
#include "stm32h7xx_hal.h"

#include "AcquisittionConf.h"
//---------------------------------------------------------------------------//
#define ACQUISITTION_PARTITION_COUNT									2
#define ACQUISITTION_PARTITION_SIZE										(ACQUISITTION_BUFFER_LENGTH / ACQUISITTION_PARTITION_COUNT)
#define ACQUISITTION_FIRST_HALT_INDEX									0
#define ACQUISITTION_SECOND_HALT_INDEX									(ACQUISITTION_FIRST_HALT_INDEX + ACQUISITTION_PARTITION_SIZE)
//---------------------------------------------------------------------------//
static TIM_HandleTypeDef *tim;
static ADC_HandleTypeDef *adc;

__attribute__((section(".dma_buffer")))
static uint16_t sample[ACQUISITTION_BUFFER_LENGTH];

static void (*acquisittionHaltTransferFinishPtr)(uint16_t *ptr, uint16_t size) = NULL;
//---------------------------------------------------------------------------//

void AcquisittionInit(TIM_HandleTypeDef *_tim, ADC_HandleTypeDef *_adc){
	tim = _tim;
	adc = _adc;
}

void AcquisittionSetupCallback(void (*functionCallback)(uint16_t *ptr, uint16_t size)){
	acquisittionHaltTransferFinishPtr = functionCallback;
}

void AcquisittionStart(){
	HAL_ADC_Start_DMA(adc, (uint32_t*)sample, ACQUISITTION_BUFFER_LENGTH);
	HAL_TIM_Base_Start(tim);
}

void AcquisittionStop(){
	HAL_ADC_Stop_DMA(adc);
    HAL_TIM_Base_Stop(tim);
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
