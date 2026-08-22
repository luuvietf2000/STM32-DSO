#include "St7789Queue.h"

//------------------------------------------------------------------------------------------------//
static St7789Msg pool[ST7789_MSG_POOL_ITEM_LENGTH];
static St7789TaskQueue queue;
//------------------------------------------------------------------------------------------------//

void St7789QueueInit(){
	queue.free = xQueueCreate(ST7789_MSG_POOL_ITEM_LENGTH, sizeof(St7789Msg*));
	queue.ready = xQueueCreate(ST7789_MSG_POOL_ITEM_LENGTH, sizeof(St7789Msg*));
	for(uint32_t i = 0; i < ST7789_MSG_POOL_ITEM_LENGTH; i++){
		St7789FreeQueuePush(pool + i, ST7789_TIMEOUT_FOREVER);
	}
}

void St7789FreeQueuePush(St7789Msg *msg, TickType_t tick){
	xQueueSend(queue.free, &msg, tick);
}

void St7789FreeQueuePop(St7789Msg **msg, TickType_t tick){
	xQueueReceive(queue.free, msg, tick);
}

void St7789ReadyQueuePush(St7789Msg *msg, TickType_t tick){
	xQueueSend(queue.ready, &msg, tick);
}

void St7789ReadyQueuePop(St7789Msg **msg, TickType_t tick){
	xQueueReceive(queue.ready, msg, tick);
}

void St7789SetAreaMsgParameter(St7789Msg *msg, uint16_t xStart, uint16_t xEnd, uint16_t yStart, uint16_t yEnd){
	msg->type = ST7789_SET_AREA;
	St7789SetAreaMsg *area = &msg->area;
	area->xStart = xStart;
	area->xEnd = xEnd;
	area->yStart = yStart;
	area->yEnd = yEnd;
}
void St7789TransferDataMsgParameter(St7789Msg *msg, uint8_t *data, uint32_t dataSize, uint16_t transferCount, uint32_t blockIndexStart){
    msg->type = ST7789_TRANSFER_DATA;
    St7789TransferDataMsg *transfer = &msg->transferData;
    transfer->data = data;
    transfer->dataSize = dataSize;
    transfer->transferCount = transferCount;
    transfer->blockIndexStart = blockIndexStart;
}
