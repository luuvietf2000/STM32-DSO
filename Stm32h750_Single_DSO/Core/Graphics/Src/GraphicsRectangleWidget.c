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


