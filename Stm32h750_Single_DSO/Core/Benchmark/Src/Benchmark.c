#include "Benchmark.h"
#include "stm32h7xx.h"
#include "core_cm7.h"

uint32_t DWT_GetTime(){
	return DWT->CYCCNT;
}

void DWT_Enable(){
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t DWT_GetElapsedUs(uint32_t start, uint32_t end){
	return (uint32_t) ((end - start) / (SystemCoreClock / 1000000U));
}
