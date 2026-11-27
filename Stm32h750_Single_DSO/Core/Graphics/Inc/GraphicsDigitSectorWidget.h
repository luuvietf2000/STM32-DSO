#ifndef GRAPHICS_INC_GRAPHICSDIGITSECTORWIDGET_H_
#define GRAPHICS_INC_GRAPHICSDIGITSECTORWIDGET_H_

#include "stdint.h"
//----------------------------------------------------------------------------------------------------------//
typedef struct {
    uint16_t size;
    uint32_t color;
} GraphicsDigitSelectorControlStyle;

typedef struct {
	uint16_t width;
	uint16_t height;
	uint32_t borderColor;
	uint16_t borderWidth;
	uint32_t fontColor;
	uint16_t fontPixel;
    GraphicsDigitSelectorControlStyle increment;
    GraphicsDigitSelectorControlStyle decrement;
    uint32_t background;
    uint32_t borderHighlightColor;
    uint32_t textColor;
    uint16_t paddingTopBottom;
    uint16_t paddingLeftRight;
} GraphicsDigitSelectorControl;

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	uint32_t background;
	uint16_t itemsDisplay;
	uint16_t padding;
	GraphicsDigitSelectorControl selectorControlStyle;
	uint32_t value;
	uint32_t maxValue;
	uint32_t minValue;
	uint16_t spacing;
	uint16_t selectedIndex;
} GraphicsDigitSectorWidget;
//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawDigitSectorWidget(GraphicsDigitSectorWidget *digitSectorWidget);
#endif /* GRAPHICS_INC_GRAPHICSDIGITSECTORWIDGET_H_ */
