#include "GraphicsRectangleWidget.h"
#include "Graphics.h"

//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawRectangleWidget(GraphicsRectangleWidget *rectangle){
	GraphicsSetAreaRequest(
		rectangle->x,
		rectangle->x + rectangle->width,
		rectangle->y,
		rectangle->y + rectangle->height
	);
	uint32_t prefecrredSize = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(rectangle->width, rectangle->height));
	uint32_t fallbackSize = GRAPHICS_GET_MAX(rectangle->width, rectangle->height) * GRAPHICS_PIXEL_PER_BYTE;
	uint8_t *data = NULL;
	uint32_t size = GraphicsGetPointerMemory(&data, prefecrredSize, fallbackSize);
	GraphicsFillColor(rectangle->color, data, size);
	uint32_t transferCount = prefecrredSize / size;
	//SCB_CleanDCache_by_Addr((uint32_t*) data, size);
	//SCB_InvalidateDCache_by_Addr((uint32_t *)data, size);
	GraphicsTransfer(data, size, transferCount);
}


