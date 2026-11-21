#ifndef BENCHMARK_INC_BENCHMARK_H_
#define BENCHMARK_INC_BENCHMARK_H_

#include "stdint.h"
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//

uint32_t DWT_GetTime();
void DWT_Enable();
uint32_t DWT_GetElapsedUs(uint32_t start, uint32_t end);

#endif /* BENCHMARK_INC_BENCHMARK_H_ */
