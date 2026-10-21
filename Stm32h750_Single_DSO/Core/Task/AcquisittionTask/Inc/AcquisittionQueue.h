#ifndef TASK_ACQUISITTIONTASK_INC_ACQUISITTIONQUEUE_H_
#define TASK_ACQUISITTIONTASK_INC_ACQUISITTIONQUEUE_H_

#include "FreeRTOS.h"
//---------------------------------------------------------------------------//
#define ACQUISITTION_TIMEOUT_FOREVER									portMAX_DELAY
#define ACQUISITTION_TIMEOUT_NONE										0
//---------------------------------------------------------------------------//
typedef enum{
	ACQUISITTION_START,
	ACQUISITTION_STOP
} AcquisittionMsgType;

typedef struct{
	AcquisittionMsgType type;
} AcquisittionMsg;
//---------------------------------------------------------------------------//
void AcquisittionQueueInit();
void AcquisitionFreeQueuePush(AcquisittionMsg *msg, TickType_t tick);
void AcquisitionFreeQueuePop(AcquisittionMsg **msg, TickType_t tick);
void AcquisitionReadyQueuePush(AcquisittionMsg *msg, TickType_t tick);
void AcquisitionReadyQueuePop(AcquisittionMsg **msg, TickType_t tick);
void AcquisittionSendMsgStop();
void AcquisittionSendMsgStart();

#endif /* TASK_ACQUISITTIONTASK_INC_ACQUISITTIONQUEUE_H_ */
