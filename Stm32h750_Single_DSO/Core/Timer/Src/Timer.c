#include "Timer.h"

//----------------------------------------------------------------------------------------------------------//
static TIM_HandleTypeDef *tim;
static void (*compareMatchEvent)(TIM_HandleTypeDef *htim);
static void (*updateEvent)(TIM_HandleTypeDef *htim);
//----------------------------------------------------------------------------------------------------------//
void TimerInit(TIM_HandleTypeDef *htim){
	tim = htim;
}

HAL_StatusTypeDef TimerStart(){
	HAL_StatusTypeDef result = HAL_TIM_Base_Start_IT(tim);
	return result;
}

HAL_StatusTypeDef TimerStop(){
	HAL_StatusTypeDef result = HAL_TIM_Base_Stop_IT(tim);
	return result;
}

HAL_StatusTypeDef TimerEnableCCx(uint32_t channel){
	HAL_StatusTypeDef result = HAL_TIM_OC_Start(tim, channel);
	return result;
}

HAL_StatusTypeDef TimerDisableCCx(uint32_t channel){
	HAL_StatusTypeDef result = HAL_TIM_OC_Stop(tim, channel);
	return result;
}

void TimerEnableCCxInterrupt(uint32_t interrupt){
	__HAL_TIM_ENABLE_IT(tim, interrupt);
}

void TimerDisableCCxInterrupt(uint32_t interrupt){
	__HAL_TIM_DISABLE_IT(tim, interrupt);
}

void TimerSetFunctionCompareMatchEvent(void (*ptr)(TIM_HandleTypeDef *htim)){
	compareMatchEvent = ptr;
}

void TimerSetFunctionUpdateEvent(void (*ptr)(TIM_HandleTypeDef *htim)){
	updateEvent = ptr;
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == tim){
		compareMatchEvent(htim);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == tim){
		updateEvent(htim);
	}
}
