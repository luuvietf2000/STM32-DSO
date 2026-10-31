#ifndef TIMER_INC_TIMER_H_
#define TIMER_INC_TIMER_H_

#include "stm32h7xx_hal.h"

//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void TimerInit(TIM_HandleTypeDef *_timerUpdateMainScreen, TIM_HandleTypeDef *_timerTriggerAdc, uint32_t _channelTriggerAdc);
HAL_StatusTypeDef TimerUpdateMainScreenStart(void);
HAL_StatusTypeDef TimerUpdateMainScreenStop(void);
HAL_StatusTypeDef TimerTriggerAdcStart(void);
HAL_StatusTypeDef TimerTriggerAdcStop(void);
void TimerSetUpdateMainScreenCallback(void (*callback)(TIM_HandleTypeDef *htim));
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* TIMER_INC_TIMER_H_ */
