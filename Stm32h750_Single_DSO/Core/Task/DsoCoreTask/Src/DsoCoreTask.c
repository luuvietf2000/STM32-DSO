#include "DsoCoreTask.h"
#include "UiControllerTask.h"
#include "Timer.h"
#include "UiControllerTaskConf.h"
#include "UiControllerTaskWaveformQueue.h"
#include "Acquisittion.h"
#include "Dso_Core_Acquisittion_Buffer.h"
#include "MdmaCopy.h"
//----------------------------------------------------------------------------------------------------------//
#define DSO_CORE_TASK_MDMA_BLOCK_COUNT																1
#define DSO_CORE_TASK_MDMA_BLOCK_BUFFER_LENGTH(length)												(length*sizeof(uint16_t))
//----------------------------------------------------------------------------------------------------------//
static void DsoCoreAdcStart();
static void DsoCoreAdcStop();
static void DsoCoreUpdateUiSignal(TIM_HandleTypeDef *htim);
static void DsoCoreUpdateUi();
static void DsoCoreAcquisittionCopyBuffer(DsoCoreAcquisittionCopyBufferMsg *param);
static void DsoCoreSendAcquisittionCopyBufferRequest(uint16_t *ptr, uint16_t size);
//----------------------------------------------------------------------------------------------------------//
void DsoCoreHandle(DsoCoreMsg *msg){
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
		case DSO_CORE_MSG_ACQUISITTION_COPY_BUFFER:
			DsoCoreAcquisittionCopyBuffer(&msg->param.acquisittionCopyBufferParam);
			break;
	}
}

void DsoCoreInit(){
	AcquisittionSetupCallback(DsoCoreSendAcquisittionCopyBufferRequest);
	UiControllerPushMainScreenInitMsg(&statusBarConfig, &measurementBarConfig);
	TimerSetUpdateMainScreenCallback(DsoCoreUpdateUiSignal);
	TimerUpdateMainScreenStart();
	DsoCoreAdcStart();
}

static void DsoCoreAcquisittionCopyBuffer(DsoCoreAcquisittionCopyBufferMsg *param){
	uint16_t *desPtr = DsoCoreGetAcquisitionBufferNextWritePtr(param->size);
	MdmaContinuousMemory(
		(uint32_t*)param->ptr,
		(uint32_t*)desPtr,
		DSO_CORE_TASK_MDMA_BLOCK_BUFFER_LENGTH(param->size),
		DSO_CORE_TASK_MDMA_BLOCK_COUNT
	);
}

static void DsoCoreUpdateUi(){
	GraphicsPoint *point;
	// Get graphics point from Acquisition
	UiControllerWaveformFreeQueuePop(&point, UI_CONTROLLER_TASK_WAVEFORM_QUEUE_TIME_FOREVER);
	uint32_t voltageMax, voltageMin;
	DsoCoreProcessAcquisitionBufferChunk(point, &voltageMax, &voltageMin);
	UiControllerPushWaveformDrawMsg(point, UI_CONTROLLER_TASK_WAVEFORM_BUFFER_LENGTH, voltageMax, voltageMax);
}

static void DsoCoreAdcStart(){
	AcquisittionStart();
	TimerTriggerAdcStart();
}

static void DsoCoreAdcStop(){
	TimerTriggerAdcStop();
	AcquisittionStop();
}

static void DsoCoreUpdateUiSignal(TIM_HandleTypeDef *htim){
	DsoCoreSendMsgFromIsr(DSO_CORE_MSG_UPDATE_UI, NULL);
}

static void DsoCoreSendAcquisittionCopyBufferRequest(uint16_t *ptr, uint16_t size){
	DsoCoreMsgParam param;
	param.acquisittionCopyBufferParam.ptr = ptr;
	param.acquisittionCopyBufferParam.size = size;
	DsoCoreSendMsgFromIsr(DSO_CORE_MSG_ACQUISITTION_COPY_BUFFER, &param);
}

