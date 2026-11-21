#include "UiControllerTask.h"
#include "UiControllerTaskWaveformQueue.h"
#include "Benchmark.h"
//----------------------------------------------------------------------------------------------------------//
static void UiControllerMainScreenInit(UiControllerMsg *msg);
static void UiControllerWaveformDraw(UiControllerMsg *msg);
//----------------------------------------------------------------------------------------------------------//
void UiControllerTaskHandle(UiControllerMsg *msg){
	switch(msg->type){
		case UI_CONTROLLER_MSG_MAIN_SCREEN_INIT:
			UiControllerMainScreenInit(msg);
			break;
		case UI_CONTROLLER_MSG_WAVEFORM_DRAW:
			UiControllerWaveformDraw(msg);
			break;
		default:
			break;
	}
}

static void UiControllerWaveformDraw(UiControllerMsg *msg){
	uint32_t start = DWT_GetTime();
	WaveformUpdate(
		msg->param.waveformParam.point,
		msg->param.waveformParam.size
	);
	uint32_t end = DWT_GetTime();
	volatile uint32_t us = DWT_GetElapsedUs(start, end);
	MeasurementBarConfig measurementBarConfig = (MeasurementBarConfig){
		msg->param.waveformParam.voltageMax,
		msg->param.waveformParam.voltageMin
	};
	MeasurementBarRequestChanged(&measurementBarConfig);
	UiControllerWaveformFreeQueuePush(
		msg->param.waveformParam.point,
		UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_FOREVER
	);
}

static void UiControllerMainScreenInit(UiControllerMsg *msg){
	MainScrrenInit(
		&msg->param.mainScreenInitParam.statusBarConfig,
		&msg->param.mainScreenInitParam.measurementBarConfig
	);
}

