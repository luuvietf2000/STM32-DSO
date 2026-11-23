#ifndef GRAPHICS_INC_GRAPHICSTEXTMENU_H_
#define GRAPHICS_INC_GRAPHICSTEXTMENU_H_

#include "GraphicsRectangleWidget.h"
#include "GraphicsTextWidget.h"
//----------------------------------------------------------------------------------------------------------//
typedef enum {
    GRAPHICS_TEXT_MENU_ITEM_AVAILABLE,
    GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE
} GraphicsTextMenuRenderState;
//----------------------------------------------------------------------------------------------------------//
typedef struct{
	char *text;
} GraphicsTextMenuItem;

typedef struct{
	GraphicsTextMenuItem *content;
	uint32_t size;
	uint32_t indexStart;
	uint32_t indexEnd;
	uint32_t selectedIndex;
} GraphicsTextMenuItems;

typedef struct{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint32_t spacing;
	uint32_t padding;
	uint32_t background;
	uint32_t highlightColor;
	GraphicsTextWidget textStyle;
	uint32_t itemsDisplay;
	GraphicsTextMenuItems items;
} GraphicsTextMenuWidget;
//----------------------------------------------------------------------------------------------------------//
void GraphicsTextMenuDraw(GraphicsTextMenuWidget *textMenuConfig);
void GraphicsTextMenuNext(GraphicsTextMenuWidget *textMenuConfig);
void GraphicsTextMenuPrevious(GraphicsTextMenuWidget *textMenuConfig);
#endif /* GRAPHICS_INC_GRAPHICSTEXTMENU_H_ */
