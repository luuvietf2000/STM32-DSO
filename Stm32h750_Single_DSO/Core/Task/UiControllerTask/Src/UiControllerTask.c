#include "UiControllerTask.h"
#include "UiControllerTaskWaveformQueue.h"
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

	WaveformUpdate(
		msg->param.waveformParam.point,
		msg->param.waveformParam.size
	);

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

