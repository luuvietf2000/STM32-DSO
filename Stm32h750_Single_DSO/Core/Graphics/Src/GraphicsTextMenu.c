#include <GraphicsTextMenu.h>
#include "GraphicsRectangleWidget.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_TEXT_MENU_BORDER_WIDTH_DEFFAULT														0
#define GRAPHICS_TEXT_MENU_CALCULATOR_HEIGHT_ITEM(height, padding, item, spacing) \
    (((height) - (2U * (padding)) - ((item) - 1U) * (spacing)) / (item))
#define GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(height, spacing, selectedIndex, indexStart) \
    (((height) + (spacing)) * ((selectedIndex) - (indexStart)))
//----------------------------------------------------------------------------------------------------------//
static void GraphicsTextMenuBackgroundDraw(GraphicsTextMenuWidget *textMenuConfig);
static void GraphicsTextMenuDrawTextBase(GraphicsTextMenuWidget *textMenuConfig, uint32_t itemHeight);
static uint32_t GraphicsTextMenuGetAvailableItemCount(GraphicsTextMenuWidget *textMenuConfig);
static GraphicsTextMenuRenderState GraphicsTextMenuGetRenderState(GraphicsTextMenuWidget *textMenuConfig);
static void GraphicsTextMenuUpdate(GraphicsTextMenuWidget *textMenuConfig, uint32_t y, uint32_t selectedIndex, uint32_t indexStartOld, uint32_t indexStartNew, uint32_t indexEndNew);
//----------------------------------------------------------------------------------------------------------//
void GraphicsTextMenuDraw(GraphicsTextMenuWidget *textMenuConfig){
	GraphicsTextMenuBackgroundDraw(textMenuConfig);
	if(GraphicsTextMenuGetRenderState(textMenuConfig) == GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE)
		return;
	uint32_t itemHeight = GRAPHICS_TEXT_MENU_CALCULATOR_HEIGHT_ITEM(
		textMenuConfig->height,
		textMenuConfig->padding,
		textMenuConfig->itemsDisplay,
		textMenuConfig->spacing
	);
	GraphicsTextMenuDrawTextBase(textMenuConfig, itemHeight);
}

static void GraphicsTextMenuDrawTextBase(GraphicsTextMenuWidget *textMenuConfig, uint32_t itemHeight){
	textMenuConfig->items.indexStart = 0;
	GraphicsTextWidget textWidget = textMenuConfig->textStyle;
	textWidget.height = itemHeight;
	textWidget.y = 0;
	textMenuConfig->items.indexEnd = GraphicsTextMenuGetAvailableItemCount(textMenuConfig);
	for(uint32_t i = textMenuConfig->items.indexStart; i < textMenuConfig->items.indexEnd; i++){
		textWidget.content = (textMenuConfig->items.content + i)->text;
		textWidget.background = textMenuConfig->items.selectedIndex == i ? textMenuConfig->highlightColor : textMenuConfig->textStyle.background;
		GraphicsDrawTextWidget(&textWidget);
		textWidget.y += itemHeight + textMenuConfig->spacing;
	}
}

static GraphicsTextMenuRenderState GraphicsTextMenuGetRenderState(GraphicsTextMenuWidget *textMenuConfig){
	uint32_t itemHeight = GRAPHICS_TEXT_MENU_CALCULATOR_HEIGHT_ITEM(
		textMenuConfig->height,
		textMenuConfig->padding,
		textMenuConfig->itemsDisplay,
		textMenuConfig->spacing
	);
	uint32_t items = GraphicsTextMenuGetAvailableItemCount(textMenuConfig);
	if(itemHeight == 0 || items == 0)
		return GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE;
	return GRAPHICS_TEXT_MENU_ITEM_AVAILABLE;
}

static uint32_t GraphicsTextMenuGetAvailableItemCount(GraphicsTextMenuWidget *textMenuConfig){
	return GRAPHICS_GET_MIN(textMenuConfig->itemsDisplay, textMenuConfig->items.size);
}

void GraphicsTextMenuPrevious(GraphicsTextMenuWidget *textMenuConfig){
	if(GraphicsTextMenuGetRenderState(textMenuConfig) == GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE)
		return;
	uint32_t yOffset = 0;
	if(textMenuConfig->items.indexStart == 0){
		if(textMenuConfig->items.selectedIndex == 0)
			return;
		yOffset = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
		    textMenuConfig->textStyle.height,
		    textMenuConfig->spacing,
		    textMenuConfig->items.selectedIndex,
			1
		);
		GraphicsTextMenuUpdate(
			textMenuConfig,
			yOffset,
			textMenuConfig->items.selectedIndex - 1,
			textMenuConfig->items.selectedIndex - 1,
			textMenuConfig->items.selectedIndex - 1,
			textMenuConfig->items.selectedIndex + 1
		);
		textMenuConfig->items.selectedIndex--;
	} else{
		GraphicsTextMenuUpdate(
			textMenuConfig,
			yOffset,
			textMenuConfig->items.selectedIndex - 1,
			textMenuConfig->items.indexStart,
			textMenuConfig->items.indexStart - 1,
			textMenuConfig->items.indexEnd - 1
		);
		textMenuConfig->items.selectedIndex--;
		textMenuConfig->items.indexStart--;
		textMenuConfig->items.indexEnd--;
	}
}

void GraphicsTextMenuNext(GraphicsTextMenuWidget *textMenuConfig){
	if(GraphicsTextMenuGetRenderState(textMenuConfig) == GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE)
		return;
	uint32_t items = GraphicsTextMenuGetAvailableItemCount(textMenuConfig);
	uint32_t indexStartLimit = textMenuConfig->items.size - items;
	uint32_t yOffset = 0;
	if(textMenuConfig->items.indexStart < indexStartLimit){
		GraphicsTextMenuUpdate(
			textMenuConfig,
			yOffset,
			textMenuConfig->items.selectedIndex + 1,
			textMenuConfig->items.indexStart,
			textMenuConfig->items.indexStart + 1,
			textMenuConfig->items.indexEnd + 1
		);
 		textMenuConfig->items.selectedIndex++;
		textMenuConfig->items.indexStart++;
		textMenuConfig->items.indexEnd++;
	} else{
		if(textMenuConfig->items.selectedIndex >= (textMenuConfig->items.size - 1))
			return;
		yOffset = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
		    textMenuConfig->textStyle.height,
		    textMenuConfig->spacing,
		    textMenuConfig->items.selectedIndex,
		    textMenuConfig->items.indexStart
		);
		GraphicsTextMenuUpdate(
			textMenuConfig,
			yOffset,
			textMenuConfig->items.selectedIndex + 1,
			textMenuConfig->items.selectedIndex,
			textMenuConfig->items.selectedIndex,
			textMenuConfig->items.selectedIndex + 2
		);
		textMenuConfig->items.selectedIndex++;
	}
}

static void GraphicsTextMenuUpdate(GraphicsTextMenuWidget *textMenuConfig, uint32_t y, uint32_t selectedIndex, uint32_t indexStartOld, uint32_t indexStartNew, uint32_t indexEndNew){
	GraphicsTextWidget textWidget = textMenuConfig->textStyle;
	textWidget.y = y;
	GraphicsTextMenuItem *itemStartOld = textMenuConfig->items.content + indexStartOld;
	GraphicsTextMenuItem *itemStartNew = textMenuConfig->items.content + indexStartNew;
	for(uint32_t i = indexStartNew; i < indexEndNew; i++){
		textWidget.background = selectedIndex == i ? textMenuConfig->highlightColor : textMenuConfig->textStyle.background;
		GraphicsTextWidgetUpdateContent(&textWidget, itemStartOld->text, itemStartNew->text);
		textWidget.y += textMenuConfig->textStyle.height + textMenuConfig->spacing;
		itemStartOld++;
		itemStartNew++;
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
