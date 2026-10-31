#include "Timer.h"

//----------------------------------------------------------------------------------------------------------//
static TIM_HandleTypeDef *timerUpdateMainScreen;
static TIM_HandleTypeDef *timerTriggerAdc;
static uint32_t channelTriggerAdc;
static void (*timerUpdateMainScreenCallback)(TIM_HandleTypeDef *htim);
//----------------------------------------------------------------------------------------------------------//
void TimerInit(TIM_HandleTypeDef *_timerUpdateMainScreen, TIM_HandleTypeDef *_timerTriggerAdc, uint32_t _channelTriggerAdc){
	timerUpdateMainScreen = _timerUpdateMainScreen;
	timerTriggerAdc = _timerTriggerAdc;
	channelTriggerAdc = _channelTriggerAdc;
}

HAL_StatusTypeDef TimerUpdateMainScreenStart(){
	HAL_StatusTypeDef result = HAL_TIM_Base_Start_IT(timerUpdateMainScreen);
	return result;
}

HAL_StatusTypeDef TimerUpdateMainScreenStop(){
	HAL_StatusTypeDef result = HAL_TIM_Base_Stop_IT(timerUpdateMainScreen);
	return result;
}

HAL_StatusTypeDef TimerTriggerAdcStart(){
	HAL_StatusTypeDef result = HAL_TIM_OC_Start(timerTriggerAdc, channelTriggerAdc);
	return result;
}

HAL_StatusTypeDef TimerTriggerAdcStop(){
	HAL_StatusTypeDef result = HAL_TIM_OC_Stop(timerTriggerAdc, channelTriggerAdc);
	return result;
}

void TimerSetUpdateMainScreenCallback(void (*callback)(TIM_HandleTypeDef *htim)){
	timerUpdateMainScreenCallback = callback;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == timerUpdateMainScreen){
		timerUpdateMainScreenCallback(htim);
	}
}
