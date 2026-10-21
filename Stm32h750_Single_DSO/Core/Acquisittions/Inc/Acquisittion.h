#ifndef ACQUISITTIONS_INC_ACQUISITTION_H_
#define ACQUISITTIONS_INC_ACQUISITTION_H_

#include "stdint.h"
#include "stm32h7xx_hal.h"
//---------------------------------------------------------------------------//
void AcquisittionInit(TIM_HandleTypeDef *_tim, ADC_HandleTypeDef *_adc);
void AcquisittionStart();
void AcquisittionStop();
void AcquisittionSetupCallback(void (*functionCallback)(uint16_t *ptr, uint16_t size));

#endif /* ACQUISITTIONS_INC_ACQUISITTION_H_ */
