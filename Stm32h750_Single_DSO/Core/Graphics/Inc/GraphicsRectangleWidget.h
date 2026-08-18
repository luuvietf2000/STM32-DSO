#ifndef GRAPHICS_INC_GRAPHICSRECTANGLEWIDGET_H_
#define GRAPHICS_INC_GRAPHICSRECTANGLEWIDGET_H_

#include "stdint.h"

//----------------------------------------------------------------------------------------------------------//
typedef struct{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint32_t color;
} GraphicsRectangleWidget;
//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawRectangleWidget(GraphicsRectangleWidget *rectangle);

#endif /* GRAPHICS_INC_GRAPHICSRECTANGLEWIDGET_H_ */
