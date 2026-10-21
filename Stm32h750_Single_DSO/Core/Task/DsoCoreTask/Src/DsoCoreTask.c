#include "DsoCoreTask.h"
#include "AcquisittionTask.h"
#include "UiControllerTask.h"
#include "Timer.h"
#include "UiControllerTaskConf.h"
#include "UiControllerTaskWaveformQueue.h"
//----------------------------------------------------------------------------------------------------------//
#define DSO_TIMER_CHANNEL																	TIMER_CHANNEL_1
//----------------------------------------------------------------------------------------------------------//
static void DsoCoreAdcStart();
static void DsoCoreAdcStop();
static void DsoCoreUpdateUiSignal(TIM_HandleTypeDef *htim);
static void DsoCoreUpdateUi();

static uint32_t iTest = 0;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreHandle(DsoCoreMsg *msg, DsoCoreMsgParam *arg){
	switch(msg->type){
		case DSO_CORE_MSG_ADC_START:
			DsoCoreAdcStart();
			break;
		case DSO_CORE_MSG_ADC_STOP:
			DsoCoreAdcStop();
			break;
		case DSO_CORE_MSG_UPDATE_UI:
			DsoCoreUpdateUi();
			break;
	}
}

void DsoCoreInit(TIM_HandleTypeDef *htim){
	TimerInit(htim);
	UiControllerPushMainScreenInitMsg(&statusBarConfig, &measurementBarConfig);
	TimerSetFunctionUpdateEvent(DsoCoreUpdateUiSignal);
	TimerStart();
}

static void DsoCoreUpdateUi(){
	GraphicsPoint *point;
	// Get graphics point from Acquisition
	UiControllerWaveformFreeQueuePop(&point, UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_FOREVER);
	for(uint32_t i = 0; i < UI_CONTROLLER_TASK_WAVEFORM_BUFFER_LENGTH; i++){
		point[i].start = 0;
		point[i].end = 1 + iTest % 150;
	}
	iTest++;
	UiControllerPushWaveformDrawMsg(point, UI_CONTROLLER_TASK_WAVEFORM_BUFFER_LENGTH);
}

static void DsoCoreAdcStart(){
	TimerEnableCCx(DSO_TIMER_CHANNEL);
}

static void DsoCoreAdcStop(){
	TimerDisableCCx(DSO_TIMER_CHANNEL);
}

static void DsoCoreUpdateUiSignal(TIM_HandleTypeDef *htim){
	DsoCoreMsg *msg = NULL;
	BaseType_t priority = pdFALSE;

	if(DsoCoreFreeQueuePopIsr(&msg, &priority) == pdPASS){
		msg->type = DSO_CORE_MSG_UPDATE_UI;
		DsoCoreReadyQueuePushIsr(msg, &priority);
	}
	portYIELD_FROM_ISR(priority);
}

