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
static uint32_t GraphicsTextMenuSetLastSelectedColor(GraphicsTextMenuWidget *textMenuConfig, uint32_t index);
static uint32_t GraphicsTextMenuSetBackGroundColor(GraphicsTextMenuWidget *textMenuConfig, uint32_t selectedIndex, uint32_t index);
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
static uint32_t GraphicsTextMenuSetLastSelectedColor(GraphicsTextMenuWidget *textMenuConfig, uint32_t index){
	if((textMenuConfig->selectionState == GRAPHICS_MENU_ITEM_SELECTED) && (textMenuConfig->items.lastSelectedIndex == index)){
		return textMenuConfig->lastSelectedColor;
	}
	return textMenuConfig->textStyle.textColor;

}

void GraphicsTextMenuSelected(GraphicsTextMenuWidget *textMenuConfig){
    GraphicsTextMenuWidget *config = textMenuConfig;
    GraphicsTextMenuItems *items = &config->items;
	if(items->lastSelectedIndex == items->selectedIndex)
		return;
    char *content = NULL;
    GraphicsTextWidget *textStyle = &config->textStyle;
    GraphicsTextWidget textWidget = *textStyle;
    if(items->lastSelectedIndex >= items->indexStart && items->lastSelectedIndex < items->indexEnd){
        textWidget.y = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
            textStyle->height,
            config->spacing,
            items->lastSelectedIndex,
            items->indexStart
        );
        content = (items->content + items->lastSelectedIndex)->text;
        textWidget.textColor = textStyle->textColor;
        GraphicsTextWidgetUpdateContent(&textWidget, content, content, config->background);
    }
    items->lastSelectedIndex = items->selectedIndex;
    textWidget.y = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
        textStyle->height,
        config->spacing,
        items->selectedIndex,
        items->indexStart
    );
    textWidget.textColor = config->lastSelectedColor;
    content = (items->content + items->selectedIndex)->text;
    GraphicsTextWidgetUpdateContent(&textWidget, content, content, config->highlightColor);
}

static uint32_t GraphicsTextMenuSetBackGroundColor(GraphicsTextMenuWidget *textMenuConfig, uint32_t selectedIndex, uint32_t index){
	if(selectedIndex == index){
		return textMenuConfig->highlightColor;
	}
	return textMenuConfig->textStyle.background;
}
static void GraphicsTextMenuDrawTextBase(GraphicsTextMenuWidget *textMenuConfig, uint32_t itemHeight){
    GraphicsTextMenuWidget *config = textMenuConfig;
    GraphicsTextMenuItems *items = &config->items;
    GraphicsTextWidget *textStyle = &config->textStyle;
    GraphicsTextWidget textWidget = *textStyle;
    textWidget.height = itemHeight;
    textWidget.y = 0;
    uint32_t itemsCount = GraphicsTextMenuGetAvailableItemCount(config);
    if(config->selectionState == GRAPHICS_MENU_ITEM_SELECTED){
        uint32_t indexStartLimit = items->size - itemsCount;
        items->indexStart = GRAPHICS_GET_MIN(indexStartLimit, items->lastSelectedIndex);
        items->indexEnd = items->indexStart + itemsCount;
        items->selectedIndex = items->lastSelectedIndex;
    } else {
        items->indexStart = 0;
        items->indexEnd = itemsCount;
    }
    for(uint32_t i = items->indexStart; i < items->indexEnd; i++){
        textWidget.content = (items->content + i)->text;
        textWidget.textColor = GraphicsTextMenuSetLastSelectedColor(config, i);
        textWidget.background = GraphicsTextMenuSetBackGroundColor(config, items->selectedIndex, i);
        GraphicsDrawTextWidget(&textWidget);
        textWidget.y += itemHeight + config->spacing;
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
    GraphicsTextMenuWidget *config = textMenuConfig;
    GraphicsTextMenuItems *infoItems = &config->items;
    GraphicsTextWidget *textStyle = &config->textStyle;
    if(GraphicsTextMenuGetRenderState(config) == GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE)
        return;
    uint32_t yOffset = 0;
    if(infoItems->selectedIndex == 0){
        return;
    }
    if(infoItems->indexStart < infoItems->selectedIndex){
        yOffset = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
            textStyle->height,
            config->spacing,
            infoItems->selectedIndex - 1,
            infoItems->indexStart
        );

        GraphicsTextMenuUpdate(
            config,
            yOffset,
            infoItems->selectedIndex - 1,
            infoItems->selectedIndex - 1,
            infoItems->selectedIndex - 1,
            infoItems->selectedIndex + 1
        );
        infoItems->selectedIndex--;
    } else{
        GraphicsTextMenuUpdate(
            config,
            yOffset,
            infoItems->selectedIndex - 1,
            infoItems->indexStart,
            infoItems->indexStart - 1,
            infoItems->indexEnd - 1
        );
        infoItems->selectedIndex--;
        infoItems->indexStart--;
        infoItems->indexEnd--;
    }
}

void GraphicsTextMenuNext(GraphicsTextMenuWidget *textMenuConfig){
    GraphicsTextMenuWidget *config = textMenuConfig;
    GraphicsTextMenuItems *infoItems = &config->items;
    GraphicsTextWidget *textStyle = &config->textStyle;
    if(GraphicsTextMenuGetRenderState(config) == GRAPHICS_TEXT_MENU_ITEM_UNAVAILABLE)
        return;
    uint32_t yOffset = 0;
    if((infoItems->size - 1) == infoItems->selectedIndex){
        return;
    }
    if((infoItems->selectedIndex + 1) < infoItems->indexEnd){
        yOffset = GRAPHICS_TEXT_MENU_SELECTED_Y_OFFSET(
            textStyle->height,
            config->spacing,
            infoItems->selectedIndex,
            infoItems->indexStart
        );
        GraphicsTextMenuUpdate(
            config,
            yOffset,
            infoItems->selectedIndex + 1,
            infoItems->selectedIndex,
            infoItems->selectedIndex,
            infoItems->selectedIndex + 2
        );
        infoItems->selectedIndex++;
    } else{
        GraphicsTextMenuUpdate(
            config,
            yOffset,
            infoItems->selectedIndex + 1,
            infoItems->indexStart,
            infoItems->indexStart + 1,
            infoItems->indexEnd + 1
        );
        infoItems->selectedIndex++;
        infoItems->indexStart++;
        infoItems->indexEnd++;
    }
}

static void GraphicsTextMenuUpdate(GraphicsTextMenuWidget *textMenuConfig, uint32_t y, uint32_t selectedIndex, uint32_t indexStartOld, uint32_t indexStartNew, uint32_t indexEndNew){
	GraphicsTextWidget textWidget = textMenuConfig->textStyle;
	textWidget.y = y;
	GraphicsTextMenuItem *itemStartOld = textMenuConfig->items.content + indexStartOld;
	GraphicsTextMenuItem *itemStartNew = textMenuConfig->items.content + indexStartNew;
	uint32_t highlight;
	for(uint32_t i = indexStartNew; i < indexEndNew; i++){
		highlight = GraphicsTextMenuSetBackGroundColor(textMenuConfig, selectedIndex, i);
		textWidget.textColor = GraphicsTextMenuSetLastSelectedColor(textMenuConfig, i);
		GraphicsTextWidgetUpdateContent(&textWidget, itemStartOld->text, itemStartNew->text, highlight);
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
