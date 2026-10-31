#include "UiControllerTaskQueue.h"
#include "UiControllerTaskConf.h"
#include "UiControllerTaskWaveformQueue.h"
//----------------------------------------------------------------------------------------------------------//
static UiControllerMsg pool[UI_CONTROLLER_TASK_QUEUE_LENGTH];
static QueueHandle_t ready;
static QueueHandle_t free;
//----------------------------------------------------------------------------------------------------------//
static void UiControllerFreeQueuePush(UiControllerMsg *msg, TickType_t tick);
static void UiControllerFreeQueuePop(UiControllerMsg **msg, TickType_t tick);
static void UiControllerReadyQueuePush(UiControllerMsg *msg, TickType_t tick);
static void UiControllerReadyQueuePop(UiControllerMsg **msg, TickType_t tick);
//----------------------------------------------------------------------------------------------------------//
void UiControllerQueueInit(){
    ready = xQueueCreate(UI_CONTROLLER_TASK_QUEUE_LENGTH, sizeof(UiControllerMsg*));
    free = xQueueCreate(UI_CONTROLLER_TASK_QUEUE_LENGTH, sizeof(UiControllerMsg*));
    for (size_t i = 0; i < UI_CONTROLLER_TASK_QUEUE_LENGTH; i++){
        UiControllerFreeQueuePush(&pool[i], 0);
    }
    UiControllerWaveformQueueInit();
}

void UiControllerPushWaveformDrawMsg(GraphicsPoint *point, uint32_t size, float voltageMax, float voltageMin){
	UiControllerContent param = {
		.waveformParam = {
			.point = point,
			.size = size,
			.voltageMax = voltageMax,
			.voltageMin = voltageMin
		}
	};
	UiControllerMsgSend(&param, UI_CONTROLLER_MSG_WAVEFORM_DRAW, UI_CONTROLLER_TASK_TIME_FOREVER);
}

void UiControllerPushMainScreenInitMsg(StatusBarConfig *statusBarParameter, MeasurementBarConfig *measurementBarParameter){
	UiControllerContent param = {
		.mainScreenInitParam = {
			.statusBarConfig = *statusBarParameter,
			.measurementBarConfig = *measurementBarParameter
		}
	};
	UiControllerMsgSend(&param, UI_CONTROLLER_MSG_MAIN_SCREEN_INIT, UI_CONTROLLER_TASK_TIME_FOREVER);
}

void UiControllerMsgRead(void (*callback)(UiControllerMsg *msg), TickType_t tick){
    UiControllerMsg *msg;
    UiControllerReadyQueuePop(&msg, tick);
    callback(msg);
    UiControllerFreeQueuePush(msg, tick);
}

void UiControllerMsgSend(UiControllerContent *arg, UiControllerMsgType type, TickType_t tick){
    UiControllerMsg *msg;
    UiControllerFreeQueuePop(&msg, tick);
    msg->type = type;
    msg->param = *arg;
    UiControllerReadyQueuePush(msg, tick);
}

static void UiControllerFreeQueuePush(UiControllerMsg *msg, TickType_t tick){
    xQueueSend(free, &msg, tick);
}

static void UiControllerFreeQueuePop(UiControllerMsg **msg, TickType_t tick){
    xQueueReceive(free, msg, tick);
}

static void UiControllerReadyQueuePush(UiControllerMsg *msg, TickType_t tick){
    xQueueSend(ready, &msg, tick);
}

static void UiControllerReadyQueuePop(UiControllerMsg **msg, TickType_t tick){
    xQueueReceive(ready, msg, tick);
}

