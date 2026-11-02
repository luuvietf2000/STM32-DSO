#include "UiControllerTaskWaveformQueue.h"


//----------------------------------------------------------------------------------------------------------//
static GraphicsPoint pool[UI_CONTROLLER_TASK_WAVEFORM_QUEUE_LENGTH][UI_CONTROLLER_TASK_WAVEFORM_BUFFER_LENGTH];
static QueueHandle_t free;
//----------------------------------------------------------------------------------------------------------//
void UiControllerWaveformQueueInit(){
    free = xQueueCreate(UI_CONTROLLER_TASK_WAVEFORM_QUEUE_LENGTH, sizeof(GraphicsPoint*));
    for (size_t i = 0; i < UI_CONTROLLER_TASK_WAVEFORM_QUEUE_LENGTH; i++){
        UiControllerWaveformFreeQueuePush(&pool[i][0], UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_FOREVER);
    }
}

void UiControllerWaveformFreeQueuePush(GraphicsPoint *point, TickType_t tick){
	xQueueSend(free, &point, tick);
}

void UiControllerWaveformFreeQueuePop(GraphicsPoint **point, TickType_t tick){
    xQueueReceive(free, point, tick);
}
