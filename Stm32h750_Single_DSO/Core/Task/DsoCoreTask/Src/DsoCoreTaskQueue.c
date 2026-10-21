#include "DsoCoreTaskQueue.h"

//----------------------------------------------------------------------------------------------------------//
static QueueHandle_t free;
static QueueHandle_t ready;
static DsoCoreMsg pool[DSO_CORE_TASK_QUEUE_LENGTH];
//----------------------------------------------------------------------------------------------------------//

void DsoCoreQueueInit(){
	free = xQueueCreate(DSO_CORE_TASK_QUEUE_LENGTH, sizeof(DsoCoreMsg*));
	ready = xQueueCreate(DSO_CORE_TASK_QUEUE_LENGTH, sizeof(DsoCoreMsg*));
	for (uint32_t i = 0; i < DSO_CORE_TASK_QUEUE_LENGTH; i++){
		DsoCoreFreeQueuePush(pool + i, DSO_CORE_TIME_FOREVER);
	}
}

void DsoCoreFreeQueuePush(DsoCoreMsg *msg, TickType_t tick){
    xQueueSend(free, &msg, tick);
}

void DsoCoreFreeQueuePop(DsoCoreMsg **msg, TickType_t tick){
    xQueueReceive(free, msg, tick);
}

void DsoCoreReadyQueuePush(DsoCoreMsg *msg, TickType_t tick){
    xQueueSend(ready, &msg, tick);
}

void DsoCoreReadyQueuePop(DsoCoreMsg **msg, TickType_t tick){
    xQueueReceive(ready, msg, tick);
}

void DsoCoreMsgRead(void (*callback)(DsoCoreMsg *msg, DsoCoreMsgParam *arg), DsoCoreMsgParam *arg, TickType_t tick){
	DsoCoreMsg *msg;
	DsoCoreReadyQueuePop(&msg, DSO_CORE_TIME_FOREVER);
	callback(msg, arg);
	DsoCoreFreeQueuePush(msg, DSO_CORE_TIME_FOREVER);
}

void DsoCoreMsgSend(void (*callback)(DsoCoreMsg *msg, DsoCoreMsgParam *arg), DsoCoreMsgParam *arg, TickType_t tick){
    DsoCoreMsg *msg;
    DsoCoreFreeQueuePop(&msg, DSO_CORE_TIME_FOREVER);
    callback(msg, arg);
    DsoCoreReadyQueuePush(msg, DSO_CORE_TIME_FOREVER);
}

BaseType_t DsoCoreFreeQueuePopIsr(DsoCoreMsg **msg, BaseType_t *priority){
	return xQueueReceiveFromISR(free, msg, priority);
}

BaseType_t DsoCoreReadyQueuePushIsr(DsoCoreMsg *msg, BaseType_t *priority){
	return xQueueSendFromISR(ready, &msg, priority);
}
