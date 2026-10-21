#include "AcquisittionTaskConf.h"
#include "AcquisittionQueue.h"
#include "FreeRTOS.h"
#include "queue.h"

//---------------------------------------------------------------------------//
static AcquisittionMsg pool[ACQUISITTION_QUEUE_SIZE];
static QueueHandle_t queueReady;
static QueueHandle_t queueFree;
//---------------------------------------------------------------------------//
void AcquisittionSendMsg(AcquisittionMsgType type);
//---------------------------------------------------------------------------//

void AcquisittionQueueInit(){
	queueReady = xQueueCreate(ACQUISITTION_QUEUE_SIZE, sizeof(AcquisittionMsg*));
	queueFree = xQueueCreate(ACQUISITTION_QUEUE_SIZE, sizeof(AcquisittionMsg*));
	for(uint32_t i = 0; i < ACQUISITTION_QUEUE_SIZE; i++)
		AcquisitionFreeQueuePush(pool + i, ACQUISITTION_TIMEOUT_NONE);
}



void AcquisitionFreeQueuePush(AcquisittionMsg *msg, TickType_t tick)
{
    xQueueSend(queueFree, &msg, tick);
}

void AcquisitionFreeQueuePop(AcquisittionMsg **msg, TickType_t tick)
{
    xQueueReceive(queueFree, msg, tick);
}

void AcquisitionReadyQueuePush(AcquisittionMsg *msg, TickType_t tick)
{
    xQueueSend(queueReady, &msg, tick);
}

void AcquisitionReadyQueuePop(AcquisittionMsg **msg, TickType_t tick)
{
    xQueueReceive(queueReady, msg, tick);
}

void AcquisittionSendMsg(AcquisittionMsgType type){
	AcquisittionMsg *msg;
	AcquisitionFreeQueuePop(&msg, ACQUISITTION_TIMEOUT_FOREVER);
	msg->type = type;
	AcquisitionReadyQueuePush(msg, ACQUISITTION_TIMEOUT_FOREVER);
}

void AcquisittionSendMsgStart(){
	AcquisittionSendMsg(ACQUISITTION_START);
}

void AcquisittionSendMsgStop(){
	AcquisittionSendMsg(ACQUISITTION_STOP);
}

