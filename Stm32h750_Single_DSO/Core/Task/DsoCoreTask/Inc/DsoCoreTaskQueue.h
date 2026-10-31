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
	DSO_CORE_MSG_UPDATE_UI,
	DSO_CORE_MSG_ACQUISITTION_COPY_BUFFER
} DsoCoreMsgType;
//----------------------------------------------------------------------------------------------------------//
typedef struct{
	uint16_t *ptr;
	uint16_t size;
} DsoCoreAcquisittionCopyBufferMsg;

typedef union{
	DsoCoreAcquisittionCopyBufferMsg acquisittionCopyBufferParam;
} DsoCoreMsgParam;

typedef struct{
	DsoCoreMsgType type;
	DsoCoreMsgParam param;
} DsoCoreMsg;
//----------------------------------------------------------------------------------------------------------//
void DsoCoreQueueInit();
void DsoCoreMsgRead(void (*callback)(DsoCoreMsg *msg), TickType_t tick);
void DsoCoreMsgSend(DsoCoreMsgType type, DsoCoreMsgParam *arg, TickType_t tick);
BaseType_t DsoCoreReadyQueuePushIsr(DsoCoreMsg *msg, BaseType_t *priority);
BaseType_t DsoCoreFreeQueuePopIsr(DsoCoreMsg **msg, BaseType_t *priority);
void DsoCoreSendAcquisittionCopyBufferRequest(uint16_t *ptr, uint16_t size);
#endif /* TASK_DSOCORETASK_INC_DSOCORETASKQUEUE_H_ */
