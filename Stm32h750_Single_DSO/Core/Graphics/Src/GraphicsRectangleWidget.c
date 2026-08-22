#include "GraphicsRectangleWidget.h"
#include "Graphics.h"

//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawRectangleWidget(GraphicsRectangleWidget *rectangle){
	if(rectangle->borderWidth != 0){
		// border top
		GraphicsDrawRectangle(
			rectangle->x,
			rectangle->y,
			rectangle->x + rectangle->width,
			rectangle->y + rectangle->borderWidth,
			rectangle->borderColor
		);

		// border left
		GraphicsDrawRectangle(
		    rectangle->x,
		    rectangle->y + rectangle->borderWidth,
		    rectangle->borderWidth,
		    rectangle->height - 2 * rectangle->borderWidth,
		    rectangle->borderColor
		);

		// border bottom
		GraphicsDrawRectangle(
		    rectangle->x,
		    rectangle->y + rectangle->height - rectangle->borderWidth,
		    rectangle->width,
		    rectangle->borderWidth,
		    rectangle->borderColor
		);

		// border right
		GraphicsDrawRectangle(
		    rectangle->x + rectangle->width - rectangle->borderWidth,
		    rectangle->y + rectangle->borderWidth,
		    rectangle->borderWidth,
		    rectangle->height - 2 * rectangle->borderWidth,
		    rectangle->borderColor
		);
	}
	GraphicsDrawRectangle(
		rectangle->x + rectangle->borderWidth,
		rectangle->y + rectangle->borderWidth,
		rectangle->width - 2 * rectangle->borderWidth,
		rectangle->height - 2 * rectangle->borderWidth,
		rectangle->color
	);
}

void GraphicsRectangleSetParameter(
    GraphicsRectangleWidget *rectangle,
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t color,
    uint32_t borderColor,
    uint32_t borderWidth)
{
    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
    rectangle->color = color;
    rectangle->borderColor = borderColor;
    rectangle->borderWidth = borderWidth;
}
