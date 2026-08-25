#include <UiDisplayBridge.h>
#include "stdio.h"
//----------------------------------------------------------------------------------------------------------//
static uint32_t sizeAlloc;
static uint32_t index;
//----------------------------------------------------------------------------------------------------------//

void GraphicsSetRowRequest(uint16_t rowStart, uint16_t rowEnd){
	St7789Msg *msg = NULL;
	St7789FreeQueuePop(&msg, ST7789_TIMEOUT_FOREVER);
	St7789SetRowMsgParameter(msg, rowStart, rowEnd);
	St7789ReadyQueuePush(msg, ST7789_TIMEOUT_FOREVER);
}

void GraphicsSetAreaRequest(uint16_t columnStart, uint16_t columnEnd, uint16_t rowStart, uint16_t rowEnd){
	St7789Msg *msg = NULL;
	St7789FreeQueuePop(&msg, ST7789_TIMEOUT_FOREVER);
	St7789SetAreaMsgParameter(msg, columnStart, columnEnd, rowStart, rowEnd);
	St7789ReadyQueuePush(msg, ST7789_TIMEOUT_FOREVER);
}

uint32_t GraphicsGetPointerMemory(uint8_t **data, uint32_t preferredSize, uint32_t faillbackSize){
	*data = St7789DmaMemoryAlloc(preferredSize, faillbackSize, &index, &sizeAlloc);
	return sizeAlloc;
}

void GraphicsTransfer(uint8_t *data, uint32_t dataSize, uint32_t transferCount){
	St7789Msg *msg = NULL;
	St7789FreeQueuePop(&msg, ST7789_TIMEOUT_FOREVER);
	St7789TransferDataMsgParameter(msg, data, dataSize, transferCount, index);
	St7789ReadyQueuePush(msg, ST7789_TIMEOUT_FOREVER);
}
