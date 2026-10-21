#ifndef TASK_DSOCORETASK_INC_DSOCORETASKQUEUE_H_
#define TASK_DSOCORETASK_INC_DSOCORETASKQUEUE_H_
#include "FreeRTOS.h"
#include "queue.h"
#include "DsoCoreTaskConf.h"

//----------------------------------------------------------------------------------------------------------//
#define DSO_CORE_TIME_FOREVER																	portMAX_DELAY
#define DSO_CORE_TIME_NONE																		0
//----------------------------------------------------------------------------------------------------------//
typedef enum{
	DSO_CORE_MSG_ADC_START,
	DSO_CORE_MSG_ADC_STOP,
	DSO_CORE_MSG_UPDATE_UI
} DsoCoreMsgType;
//----------------------------------------------------------------------------------------------------------//
typedef union{

} DsoCoreMsgParam;

typedef struct{
	DsoCoreMsgType type;
	DsoCoreMsgParam param;
} DsoCoreMsg;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreQueueInit();
void DsoCoreMsgSend(void (*callback)(DsoCoreMsg *msg, DsoCoreMsgParam *arg), DsoCoreMsgParam *arg, TickType_t tick);
void DsoCoreMsgRead(void (*callback)(DsoCoreMsg *msg, DsoCoreMsgParam *arg), DsoCoreMsgParam *arg, TickType_t tick);
void DsoCoreFreeQueuePush(DsoCoreMsg *msg, TickType_t tick);
void DsoCoreFreeQueuePop(DsoCoreMsg **msg, TickType_t tick);
void DsoCoreReadyQueuePush(DsoCoreMsg *msg, TickType_t tick);
void DsoCoreReadyQueuePop(DsoCoreMsg **msg, TickType_t tick);
BaseType_t DsoCoreReadyQueuePushIsr(DsoCoreMsg *msg, BaseType_t *priority);
BaseType_t DsoCoreFreeQueuePopIsr(DsoCoreMsg **msg, BaseType_t *priority);
#endif /* TASK_DSOCORETASK_INC_DSOCORETASKQUEUE_H_ */
