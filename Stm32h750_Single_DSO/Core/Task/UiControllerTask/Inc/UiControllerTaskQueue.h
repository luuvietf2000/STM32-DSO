#ifndef TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKQUEUE_H_
#define TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKQUEUE_H_

#include "MainScreen.h"
#include "FreeRTOS.h"
#include "queue.h"
//----------------------------------------------------------------------------------------------------------//
#define UI_CONTROLLER_TASK_TIME_FOREVER															portMAX_DELAY
#define UI_CONTROLLER_TASK_TIME_NONE															0
//----------------------------------------------------------------------------------------------------------//
typedef enum{
	UI_CONTROLLER_MSG_MAIN_SCREEN_INIT,
	UI_CONTROLLER_MSG_WAVEFORM_DRAW
} UiControllerMsgType;
//----------------------------------------------------------------------------------------------------------//
typedef struct{
	StatusBarConfig statusBarConfig;
	MeasurementBarConfig measurementBarConfig;
} UiControllerMsgMainScreenInitParam;

typedef struct{
	GraphicsPoint *point;
	uint32_t size;
	float voltageMax;
	float voltageMin;
} UicontrollerMsgWaveformDraw;

typedef union{
	UiControllerMsgMainScreenInitParam mainScreenInitParam;
	UicontrollerMsgWaveformDraw waveformParam;
} UiControllerContent;

typedef struct{
	UiControllerMsgType type;
	UiControllerContent param;
} UiControllerMsg;
//----------------------------------------------------------------------------------------------------------//
void UiControllerPushMainScreenInitMsg(StatusBarConfig *statusBarParameter, MeasurementBarConfig *measurementBarParameter);
void UiControllerQueueInit();
void UiControllerMsgSend(UiControllerContent *arg, UiControllerMsgType type, TickType_t tick);
void UiControllerMsgRead(void (*callback)(UiControllerMsg *msg), TickType_t tick);
void UiControllerPushWaveformDrawMsg(GraphicsPoint *point, uint32_t size, float voltageMax, float voltageMin);
#endif /* TASK_UICONTROLLERTASK_INC_UICONTROLLERTASKQUEUE_H_ */
