#include "St7789Task.h"
#include "St7789.h"
//------------------------------------------------------------------------------------------------//
static void St7789HandleSetAreaMsg(St7789SetAreaMsg *area);
static void St7789HandleTransferData(St7789TransferDataMsg *transferData);
//------------------------------------------------------------------------------------------------//
void St7789TaskHandle(St7789Msg *msg){
	switch(msg->type){
		case ST7789_SET_AREA:
			St7789HandleSetAreaMsg(&msg->area);
			break;
		case ST7789_TRANSFER_DATA:
			St7789HandleTransferData(&msg->transferData);
			break;
	}
}

static void St7789HandleSetAreaMsg(St7789SetAreaMsg *area){
	St7789SetColumnAddress(area->xStart, area->xEnd);
	St7789SetRowAddress(area->yStart, area->yEnd);
	St7789RequestStartTransferData();
}

static void St7789HandleTransferData(St7789TransferDataMsg *transferData){
	St7789ClearCacheEnum cacheClearMode;
	for(uint32_t count = 0; count < transferData->transferCount; count++){
		cacheClearMode = count == 0 ? ST7789_CLEAR_D_CACHE : ST7789_CLEAR_NOT_D_CACHE;
		St7789WriteData(transferData->data, transferData->dataSize, cacheClearMode);
	}
}
