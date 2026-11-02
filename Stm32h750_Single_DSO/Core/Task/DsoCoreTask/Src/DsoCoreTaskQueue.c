#include "DsoCoreTaskQueue.h"

//----------------------------------------------------------------------------------------------------------//
static QueueHandle_t free;
static QueueHandle_t ready;
static DsoCoreMsg pool[DSO_CORE_TASK_QUEUE_LENGTH];
//----------------------------------------------------------------------------------------------------------//
static void DsoCoreFreeQueuePush(DsoCoreMsg *msg, TickType_t tick);
static void DsoCoreFreeQueuePop(DsoCoreMsg **msg, TickType_t tick);
static void DsoCoreReadyQueuePush(DsoCoreMsg *msg, TickType_t tick);
static void DsoCoreReadyQueuePop(DsoCoreMsg **msg, TickType_t tick);
//----------------------------------------------------------------------------------------------------------//
void DsoCoreQueueInit(){
	free = xQueueCreate(DSO_CORE_TASK_QUEUE_LENGTH, sizeof(DsoCoreMsg*));
	ready = xQueueCreate(DSO_CORE_TASK_QUEUE_LENGTH, sizeof(DsoCoreMsg*));
	for (uint32_t i = 0; i < DSO_CORE_TASK_QUEUE_LENGTH; i++){
		DsoCoreFreeQueuePush(pool + i, DSO_CORE_TIME_FOREVER);
	}

}

static void DsoCoreFreeQueuePush(DsoCoreMsg *msg, TickType_t tick){
    xQueueSend(free, &msg, tick);
}

static void DsoCoreFreeQueuePop(DsoCoreMsg **msg, TickType_t tick){
    xQueueReceive(free, msg, tick);
}

static void DsoCoreReadyQueuePush(DsoCoreMsg *msg, TickType_t tick){
    xQueueSend(ready, &msg, tick);
}

static void DsoCoreReadyQueuePop(DsoCoreMsg **msg, TickType_t tick){
    xQueueReceive(ready, msg, tick);
}

void DsoCoreMsgRead(void (*callback)(DsoCoreMsg *msg), TickType_t tick){
	DsoCoreMsg *msg;
	DsoCoreReadyQueuePop(&msg, DSO_CORE_TIME_FOREVER);
	callback(msg);
	DsoCoreFreeQueuePush(msg, DSO_CORE_TIME_FOREVER);
}

void DsoCoreMsgSend(DsoCoreMsgType type, DsoCoreMsgParam *arg, TickType_t tick){
    DsoCoreMsg *msg;
    DsoCoreFreeQueuePop(&msg, DSO_CORE_TIME_FOREVER);
    msg->type = type;
    msg->param = *arg;
    DsoCoreReadyQueuePush(msg, DSO_CORE_TIME_FOREVER);
}

BaseType_t DsoCoreFreeQueuePopIsr(DsoCoreMsg **msg, BaseType_t *priority){
	return xQueueReceiveFromISR(free, msg, priority);
}

BaseType_t DsoCoreReadyQueuePushIsr(DsoCoreMsg *msg, BaseType_t *priority){
	return xQueueSendFromISR(ready, &msg, priority);
}

void DsoCoreSendMsgFromIsr(DsoCoreMsgType type, DsoCoreMsgParam *arg){
	DsoCoreMsg *msg = NULL;
	BaseType_t priority = pdFALSE;

	if(DsoCoreFreeQueuePopIsr(&msg, &priority) == pdPASS){
		msg->type = type;
		if(arg != NULL)
			msg->param = *arg;
		DsoCoreReadyQueuePushIsr(msg, &priority);
	}
	portYIELD_FROM_ISR(priority);
}

