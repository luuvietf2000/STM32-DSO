#ifndef TIMER_INC_TIMER_H_
#define TIMER_INC_TIMER_H_

#include "stm32h7xx_hal.h"

//----------------------------------------------------------------------------------------------------------//
#define TIMER_CHANNEL_IT_1																			TIM_IT_CC1
#define TIMER_CHANNEL_1																				TIM_CHANNEL_1
//----------------------------------------------------------------------------------------------------------//

void TimerInit(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef TimerStart();
HAL_StatusTypeDef TimerStop();
void TimerEnableCCxInterrupt(uint32_t interrupt);
void TimerDisableCCxInterrupt(uint32_t interrupt);
void TimerSetFunctionCompareMatchEvent(void (*ptr)(TIM_HandleTypeDef *htim));
void TimerSetFunctionUpdateEvent(void (*ptr)(TIM_HandleTypeDef *htim));
HAL_StatusTypeDef TimerEnableCCx(uint32_t channel);
HAL_StatusTypeDef TimerDisableCCx(uint32_t channel);

#endif /* TIMER_INC_TIMER_H_ */
