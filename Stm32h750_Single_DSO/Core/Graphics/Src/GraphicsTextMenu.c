#include <GraphicsTextMenu.h>
#include "GraphicsRectangleWidget.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_TEXT_MENU_BORDER_WIDTH_DEFFAULT														0
#define GRAPHICS_TEXT_MENU_CALCULATOR_HEIGHT_ITEM(height, padding, item, spacing) \
    (((height) - (2U * (padding)) - ((item) - 1U) * (spacing)) / (item))
//----------------------------------------------------------------------------------------------------------//
static void GraphicsTextMenuBackgroundDraw(GraphicsTextMenuWidget *textMenuConfig);
static void GraphicsTextMenuDrawTextBase(GraphicsTextMenuWidget *textMenuConfig, uint32_t itemHeight);
//----------------------------------------------------------------------------------------------------------//
void GraphicsTextMenuDraw(GraphicsTextMenuWidget *textMenuConfig){
	GraphicsTextMenuBackgroundDraw(textMenuConfig);
	uint32_t itemHeight = GRAPHICS_TEXT_MENU_CALCULATOR_HEIGHT_ITEM(
		textMenuConfig->height,
		textMenuConfig->padding,
		textMenuConfig->itemsDisplay,
		textMenuConfig->spacing
	);
	if(itemHeight == 0)
		return;
	GraphicsTextMenuDrawTextBase(textMenuConfig, itemHeight);
}

static void GraphicsTextMenuDrawTextBase(GraphicsTextMenuWidget *textMenuConfig, uint32_t itemHeight){
	textMenuConfig->items.indexStart = 0;
	textMenuConfig->items.indexEnd = textMenuConfig->itemsDisplay;
	GraphicsTextWidget textWidget = textMenuConfig->textStyle;
	for(uint32_t i = textMenuConfig->items.indexStart; i < textMenuConfig->items.indexEnd; i++){
		textWidget.content = (textMenuConfig->items.content + i)->text;
		textWidget.height += itemHeight;
		textWidget.textColor = textMenuConfig->items.selectedIndex == i ? textMenuConfig->highlightColor : textMenuConfig->textStyle.textColor;
		GraphicsDrawTextWidget(&textWidget);
	}
}

static void GraphicsTextMenuBackgroundDraw(GraphicsTextMenuWidget *textMenuConfig){
	GraphicsRectangleWidget background;
	GraphicsRectangleSetParameter(
		&background,
		textMenuConfig->x,
		textMenuConfig->y,
		textMenuConfig->width,
		textMenuConfig->height,
		textMenuConfig->background,
		textMenuConfig->background,
		GRAPHICS_TEXT_MENU_BORDER_WIDTH_DEFFAULT
	);
	GraphicsDrawRectangleWidget(&background);
}
