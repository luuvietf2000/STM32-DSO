#include "GraphicsTextWidget.h"
#include "AsciiDeffaultFont.h"
#include "string.h"

//----------------------------------------------------------------------------------------------------------//
static void CalculatorTextDisplaySize(GraphicsTextWidget *text, uint32_t *columnDisplay, uint32_t *rowDisplay);
static void ConvertBitMask8bit(uint8_t *data, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDisplay, uint32_t rowDisplay);
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawTextWidget(GraphicsTextWidget *text){
	GraphicsSetMode(GRAPHICS_DMA2D_MODE_BLEND_BG);
	uint32_t xDisplay, yDisplay;
	uint32_t columnDisplay, rowDisplay;
	CalculatorTextDisplaySize(text, &columnDisplay, &rowDisplay);
	GraphiscsSetAlignment(
		text->aligment,
		text->width,
		text->height,
		columnDisplay,
		rowDisplay,
		text->x,
		text->y,
		&xDisplay,
		&yDisplay
	);
	if(rowDisplay == 0)
		return;
	GraphicsSetAreaRequest(
		xDisplay,
		xDisplay + columnDisplay,
		yDisplay,
		yDisplay + rowDisplay
	);
	uint32_t prefecrredSize = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(columnDisplay, rowDisplay));
	uint32_t fallbackSize = GRAPHICS_GET_MIN(GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_MAX(columnDisplay, rowDisplay)), GRAPHICS_BUFFER_SIZE);
	uint8_t *buffer = graphicsBuffer;
	uint8_t *data = NULL;
	uint32_t size = prefecrredSize;
	uint32_t row = 0;
	for(uint32_t i = 0; i < prefecrredSize / size; i++){
		size = GraphicsGetPointerMemory(&data, size, fallbackSize);
		row = i + (prefecrredSize == size ? rowDisplay : 1);
		ConvertBitMask8bit(buffer, text, i, columnDisplay, row);
		GraphicsConvertColors(text->textColor, text->background, buffer, data, size / GRAPHICS_PIXEL_PER_BYTE, 1);
		GraphicsTransfer(data, size, GRAPHICS_TEXT_TRANSFER_COUNT);
	}
}

static void ConvertBitMask8bit(uint8_t *data, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDisplay, uint32_t rowDisplay){
	uint32_t pos = 0;
	uint32_t indexContent, indexBitMap, indexColumnBitMap, columnBitMap, shift;
	uint32_t indexData = 0;
	for(; rowCurrent < rowDisplay; rowCurrent++){
		shift = rowCurrent / text->fontPixel;
		for(uint32_t column = 0; column < columnDisplay; column ++){
			pos = (column / text->fontPixel) % GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT;
			if(pos >= GRAPHICS_TEXT_FONT_COLUMN_SIZE)
				data[indexData] = GRAPHICS_BIT_MASK_8_BIT_MIN;
			else {
				indexContent = column / text->fontPixel / GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT;
				indexBitMap = text->content[indexContent] * GRAPHICS_TEXT_FONT_COLUMN_SIZE;
				indexColumnBitMap = indexBitMap + pos;
				columnBitMap = GRAPHICS_ACSII(indexColumnBitMap);
				data[indexData] = GRAPHICS_GET_BIT(columnBitMap, shift, GRAPHICS_TEXT_MASK) == GRAPHICS_TEXT_MASK ? GRAPHICS_BIT_MASK_8_BIT_MAX : GRAPHICS_BIT_MASK_8_BIT_MIN;
			}
			indexData++;
		}
	}
}

static void CalculatorTextDisplaySize(GraphicsTextWidget *text, uint32_t *columnDisplay, uint32_t *rowDisplay){
	uint8_t length = strlen(text->content);

	// Get length char display max
	*columnDisplay = text->width / GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT / text->fontPixel;
	*rowDisplay =  text->height / GRAPHICS_TEXT_ROW_SIZE_DEFFAULT / text->fontPixel;

	// Get length char display on tft
	length = length < *columnDisplay ? length : *columnDisplay;
	length = *rowDisplay > 0 ? length : 0;

	// Get column and row display size
	*columnDisplay = length * (GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT * text->fontPixel);
	*rowDisplay = (GRAPHICS_TEXT_ROW_SIZE_DEFFAULT * text->fontPixel);
}
