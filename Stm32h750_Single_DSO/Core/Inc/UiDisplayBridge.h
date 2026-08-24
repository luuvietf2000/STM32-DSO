#ifndef INC_UIDISPLAYBRIDGE_H_
#define INC_UIDISPLAYBRIDGE_H_

#include "St7789Task.h"
#include "Graphics.h"

void GraphicsSetAreaRequest(uint16_t columnStart, uint16_t columnEnd, uint16_t rowStart, uint16_t rowEnd);

uint32_t GraphicsGetPointerMemory(uint8_t **data, uint32_t preferredSize, uint32_t faillbackSize);

void GraphicsTransfer(uint8_t *data, uint32_t dataSize, uint32_t transferCount);

#endif /* INC_UIDISPLAYBRIDGE_H_ */
