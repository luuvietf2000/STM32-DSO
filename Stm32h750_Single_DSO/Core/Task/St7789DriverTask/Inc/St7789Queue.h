#ifndef TASK_ST7789DRIVERTASK_INC_ST7789QUEUE_H_
#define TASK_ST7789DRIVERTASK_INC_ST7789QUEUE_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "St7789Conf.h"
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
typedef enum{
	ST7789_SET_AREA,
	ST7789_TRANSFER_DATA
} St7789MsgType;

//------------------------------------------------------------------------------------------------//

typedef struct{
	uint16_t xStart;
	uint16_t yStart;
	uint16_t xEnd;
	uint16_t yEnd;
} St7789SetAreaMsg;

typedef struct{
	uint8_t *data;
	uint32_t dataSize;
	uint16_t transferCount;
	uint32_t blockIndexStart;
	uint32_t sizeAlloc;
} St7789TransferDataMsg;

typedef struct{
	St7789MsgType type;
	union{
		St7789SetAreaMsg area;
		St7789TransferDataMsg transferData;
	};
} St7789Msg;

typedef struct{
	St7789Msg *pool;
	QueueHandle_t ready;
	QueueHandle_t free;
} St7789TaskQueue;
//------------------------------------------------------------------------------------------------//
void St7789QueueInit();
void St7789FreeQueuePush(St7789Msg *msg, TickType_t tick);
void St7789FreeQueuePop(St7789Msg **msg, TickType_t tick);
void St7789ReadyQueuePush(St7789Msg *msg, TickType_t tick);
void St7789ReadyQueuePop(St7789Msg **msg, TickType_t tick);
void St7789SetAreaMsgParameter(St7789Msg *msg, uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd);
void St7789TransferDataMsgParameter(St7789Msg *msg, uint8_t *data, uint32_t dataSize, uint16_t transferCount, uint32_t blockIndexStart, uint32_t sizeAlloc);
#endif /* TASK_ST7789DRIVERTASK_INC_ST7789QUEUE_H_ */
