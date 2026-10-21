#ifndef TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKWAVEFORMQUEUE_H_
#define TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKWAVEFORMQUEUE_H_

#include "GraphicsWaveformWidget.h"
#include "UiControllerTaskConf.h"
#include "FreeRTOS.h"
#include "queue.h"
//----------------------------------------------------------------------------------------------------------//
#define UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_FOREVER											portMAX_DELAY
#define UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_NONE												0
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
void UiControllerWaveformFreeQueuePush(GraphicsPoint *point, TickType_t tick);
void UiControllerWaveformFreeQueuePop(GraphicsPoint **point, TickType_t tick);
void UiControllerWaveformQueueInit();
#endif /* TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKWAVEFORMQUEUE_H_ */
