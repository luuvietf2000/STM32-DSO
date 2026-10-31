#ifndef TASK_DSOCORETASK_INC_DSOCORETASK_H_
#define TASK_DSOCORETASK_INC_DSOCORETASK_H_

#include "DsoCoreTaskQueue.h"
#include "stm32h7xx_hal.h"
#include "DsoCoreModeConfig.h"
//----------------------------------------------------------------------------------------------------------//
extern MeasurementBarConfig measurementBarConfig;
extern StatusBarConfig statusBarConfig;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreHandle(DsoCoreMsg *msg);
void DsoCoreInit();
#endif /* TASK_DSOCORETASK_INC_DSOCORETASK_H_ */
