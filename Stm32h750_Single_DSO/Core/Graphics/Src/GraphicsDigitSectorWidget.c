#include "GraphicsDigitSectorWidget.h"
#include "GraphicsRectangleWidget.h"
#include "Graphics.h"
#include "GraphicsTextWidget.h"
#include "math.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_DIGIT_SELECTOR_CALCULATE_ITEM_SIZES(size, padding, item, spacing) \
    (size - 2U * (padding) - (item - 1U) * spacing)

#define GRAPHICS_DIGIT_SELECTOR_CALCULATE_CONTENT_SIZE(size, padding) \
    (size - (2U * padding))

#define GRAPHICS_DIGIT_SELECTOR_CALCULATE_HEIGHT(parent, child) \
	((parent) - (child))
//----------------------------------------------------------------------------------------------------------//
static void GraphicsDigitSectorDrawBackground(GraphicsDigitSectorWidget *digitSectorWidget);
static void GraphicsDrawDigitSectorBase(GraphicsDigitSectorWidget *digitSectorWidget);
//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawDigitSectorWidget(GraphicsDigitSectorWidget *digitSectorWidget){
	GraphicsDigitSectorDrawBackground(digitSectorWidget);
	GraphicsDrawDigitSectorBase(digitSectorWidget);
}

static uint32_t GraphicsGetBorderColor(GraphicsDigitSectorWidget *digitSectorWidget, uint16_t index){
	GraphicsDigitSelectorControl *infoItem = &digitSectorWidget->selectorControlStyle;
	if(digitSectorWidget->selectedIndex == index)
		return infoItem->borderHighlightColor;
	return infoItem->borderColor;
}

static void GraphicsDrawDigitSectorBase(GraphicsDigitSectorWidget *digitSectorWidget){
	GraphicsDigitSelectorControl *infoItem = &digitSectorWidget->selectorControlStyle;
	int32_t widthItems = GRAPHICS_DIGIT_SELECTOR_CALCULATE_ITEM_SIZES(
		digitSectorWidget->width,
		digitSectorWidget->padding,
		digitSectorWidget->itemsDisplay,
		digitSectorWidget->spacing
	);
	int32_t heightItems = GRAPHICS_DIGIT_SELECTOR_CALCULATE_CONTENT_SIZE(
		digitSectorWidget->height,
		digitSectorWidget->padding
	);
	widthItems = GRAPHICS_GET_MIN(
		widthItems,
		infoItem->width * digitSectorWidget->itemsDisplay + (digitSectorWidget->itemsDisplay - 1) *digitSectorWidget->spacing
	);
	heightItems = GRAPHICS_GET_MIN(heightItems, infoItem->height);
	if(widthItems ==  0 || heightItems == 0)
		return;
	uint32_t x, y;
	GraphicsSetAlignment(
		GRAPHICS_ALIGNMENT_CENTER,
		digitSectorWidget->width,
		digitSectorWidget->height,
		(uint16_t)widthItems,
		(uint16_t)heightItems,
		digitSectorWidget->x,
		digitSectorWidget->y,
		&x,
		&y
	);
	digitSectorWidget->selectedIndex = 0;
	uint32_t widthItem = (widthItems - (digitSectorWidget->itemsDisplay - 1) *digitSectorWidget->spacing) / digitSectorWidget->itemsDisplay;
	GraphicsRectangleWidget rectangleWidget;
	GraphicsRectangleSetParameter(
		&rectangleWidget,
		x,
		y,
		widthItem,
		heightItems,
		infoItem->background,
		infoItem->borderColor,
		infoItem->borderWidth
	);
	const uint16_t widthText = GRAPHICS_DIGIT_SELECTOR_CALCULATE_CONTENT_SIZE(
		widthItem,
		infoItem->paddingLeftRight
	);
	char content[2];
	content[1] = '\0';
	uint16_t heightItem = GRAPHICS_DIGIT_SELECTOR_CALCULATE_HEIGHT(heightItems, infoItem->paddingTopBottom) / 3;
	GraphicsTextWidget incrementWidget = {
		.alignment = GRAPHICS_ALIGNMENT_CENTER,
		.background = infoItem->background,
		.fontPixel = infoItem->increment.size,
		.height = heightItem,
		.textColor = infoItem->increment.color,
		.width = widthText,
		.x = x + infoItem->paddingLeftRight,
		.y = y + infoItem->paddingTopBottom ,
		.content = "+"
	};
	GraphicsTextWidget textWidget = {
		.alignment = GRAPHICS_ALIGNMENT_CENTER,
		.background = infoItem->background,
		.fontPixel = infoItem->fontPixel,
		.height = heightItem,
		.textColor = infoItem->textColor,
		.width = widthText,
		.x = x + infoItem->paddingLeftRight,
		.y = y + infoItem->paddingTopBottom + heightItem,
		.content = content
	};

	GraphicsTextWidget decrementWidget = {
		.alignment = GRAPHICS_ALIGNMENT_CENTER,
		.background = infoItem->background,
		.fontPixel = infoItem->decrement.size,
		.height = heightItem,
		.textColor = infoItem->decrement.color,
		.width = widthText,
		.x = x + infoItem->paddingLeftRight,
		.y = y + infoItem->paddingTopBottom + heightItem * 2,
		.content = "-"
	};
	uint32_t digit = (uint32_t)pow(10, digitSectorWidget->itemsDisplay - 1U);
	uint32_t xOffset = widthItem + digitSectorWidget->spacing;
	for(uint32_t i = 0; i < digitSectorWidget->itemsDisplay; i++){
	    content[0] = '0' + (digitSectorWidget->value / digit) % 10U;
		rectangleWidget.borderColor = GraphicsGetBorderColor(digitSectorWidget, i);
		GraphicsDrawRectangleWidget(&rectangleWidget);
		GraphicsDrawTextWidget(&incrementWidget);
		GraphicsDrawTextWidget(&decrementWidget);
		GraphicsDrawTextWidget(&textWidget);
		rectangleWidget.x += xOffset;
		textWidget.x += xOffset;
		incrementWidget.x += xOffset;
		decrementWidget.x += xOffset;
	    digit /= 10U;
	}
}

static void GraphicsDigitSectorDrawBackground(GraphicsDigitSectorWidget *digitSectorWidget){
	GraphicsRectangleWidget rectangleWidget;
	GraphicsRectangleSetParameter(
		&rectangleWidget,
		digitSectorWidget->x,
		digitSectorWidget->y,
		digitSectorWidget->width,
		digitSectorWidget->height,
		digitSectorWidget->background,
		0,
		0
	);
	GraphicsDrawRectangleWidget(&rectangleWidget);
}
