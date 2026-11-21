#include "GraphicsTextWidget.h"
#include "AsciiDeffaultFont.h"
#include "string.h"

//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_TEXT_CALCULATO_POSITIVE_DIFFERENCE(one, two)											(one > two ? one - two : 0)
//----------------------------------------------------------------------------------------------------------//
static void CalculatorTextDisplaySize(GraphicsTextWidget *text, uint32_t length, uint32_t *columnDisplay, uint32_t *rowDisplay);
static void ConvertBitMask8bit(uint8_t *data, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDrawAreaStart, uint32_t columnDrawAreaEnd, uint32_t rowDrawAreaStart, uint32_t rowDrawAreaEnd, uint32_t columnEnd, uint32_t rowEnd);
static void GraphicsRenderTextContent(GraphicsTextWidget *text, uint16_t xDisplay, uint16_t yDisplay, uint16_t columnDisplay, uint16_t rowDisplay, uint16_t columnStart, uint16_t columnEnd, uint16_t rowStart, uint16_t rowEnd);
static void GraphicsCalculateTextDisplayPosition(GraphicsTextWidget *text, uint32_t length, uint32_t *xDisplay, uint32_t *yDisplay, uint32_t *columnDisplay, uint32_t *rowDisplay);
//----------------------------------------------------------------------------------------------------------//


void GraphicsDrawTextWidget(GraphicsTextWidget *text){
	GraphicsSetMode(GRAPHICS_DMA2D_MODE_BLEND_BG);
	uint32_t xDisplay, yDisplay;
	uint32_t columnDisplay, rowDisplay;
	uint8_t length = strlen(text->content);
	GraphicsCalculateTextDisplayPosition(
		text,
		length,
		&xDisplay,
		&yDisplay,
		&columnDisplay,
		&rowDisplay
	);
	GraphicsRenderTextContent(
		text,
		xDisplay,
		yDisplay,
		columnDisplay,
		rowDisplay,
		0,
		columnDisplay,
		0,
		rowDisplay
	);
}

static void GraphicsCalculateTextDisplayPosition(GraphicsTextWidget *text, uint32_t length, uint32_t *xDisplay, uint32_t *yDisplay, uint32_t *columnDisplay, uint32_t *rowDisplay){
    CalculatorTextDisplaySize(text, length, columnDisplay, rowDisplay);
    GraphiscsSetAlignment(
    	text->alignment,
		text->width,
		text->height,
        *columnDisplay,
		*rowDisplay,
		text->x,
		text->y,
		xDisplay,
		yDisplay
	);
}

static void GraphicsRenderTextContent(GraphicsTextWidget *text, uint16_t xDisplay, uint16_t yDisplay, uint16_t columnDisplay, uint16_t rowDisplay, uint16_t columnStart, uint16_t columnEnd, uint16_t rowStart, uint16_t rowEnd){
    if(rowDisplay == 0 || columnDisplay == 0)
        return;
    GraphicsSetAreaRequest(
        xDisplay,
        xDisplay + columnDisplay,
        yDisplay,
        yDisplay + rowDisplay
    );
	uint32_t preferredSize  = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(columnDisplay, rowDisplay));
	uint32_t fallbackSize = GRAPHICS_GET_MIN(GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_MAX(columnDisplay, rowDisplay)), GRAPHICS_BUFFER_SIZE);
    uint8_t *buffer = graphicsBuffer;
    uint8_t *data = NULL;
    uint32_t size = preferredSize ;
    uint32_t row = 0;
    for(uint32_t i = 0; i < preferredSize / size; i++){
        size = GraphicsGetPointerMemory(&data, size, fallbackSize);
        row = i + (preferredSize  == size ? rowDisplay : 1);
        ConvertBitMask8bit(
            buffer,
            text,
            i,
            columnStart,
			columnEnd,
            rowStart,
            rowEnd,
            columnDisplay,
            row
        );

        GraphicsConvertColors(
            text->textColor,
            text->background,
            buffer,
            data,
            size / GRAPHICS_PIXEL_PER_BYTE,
            1
        );
        GraphicsTransfer( data, size, GRAPHICS_TEXT_TRANSFER_COUNT);
    }
}
void GraphicsTextWidgetUpdateContent(GraphicsTextWidget *text, char *textOld, char *textNew){
	GraphicsSetMode(GRAPHICS_DMA2D_MODE_BLEND_BG);
	uint32_t row, column;
	uint32_t columnDisplayNew, rowDisplayNew;
	uint32_t xDisplayNew, yDisplayNew;

	uint32_t lengthNew = strlen(textNew);
	uint32_t lengthOld = strlen(textOld);
	uint32_t lengthMax = GRAPHICS_GET_MAX(lengthNew, lengthOld);
	uint32_t xDisplay, yDisplay;
	GraphicsCalculateTextDisplayPosition(text, lengthMax, &xDisplay, &yDisplay, &column, &row);
	GraphicsCalculateTextDisplayPosition(text, lengthNew, &xDisplayNew, &yDisplayNew, &columnDisplayNew, &rowDisplayNew);

	strcpy(textOld, textNew);
	uint32_t columnStart = GRAPHICS_TEXT_CALCULATO_POSITIVE_DIFFERENCE(xDisplayNew, xDisplay);
	uint32_t rowStart = GRAPHICS_TEXT_CALCULATO_POSITIVE_DIFFERENCE(yDisplayNew, yDisplay);
	GraphicsRenderTextContent(
		text,
		xDisplay,
		yDisplay,
		column,
		row,
		columnStart,
		columnStart + columnDisplayNew,
		rowStart,
		rowStart + rowDisplayNew
	);
}


static void ConvertBitMask8bit(uint8_t *data, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDrawAreaStart, uint32_t columnDrawAreaEnd, uint32_t rowDrawAreaStart, uint32_t rowDrawAreaEnd, uint32_t columnEnd, uint32_t rowEnd){
	uint32_t pos = 0;
	uint32_t indexContent, indexBitMap, indexColumnBitMap, columnBitMap, shift;
	uint32_t indexData = 0;
	uint32_t columnOffset;
	for(; rowCurrent < rowEnd; rowCurrent++){
		shift = rowCurrent / text->fontPixel;
		for(uint32_t column = 0; column < columnEnd; column ++){
			if(rowCurrent < rowDrawAreaStart || rowCurrent > rowDrawAreaEnd || column < columnDrawAreaStart || column > columnDrawAreaEnd){
				data[indexData] = GRAPHICS_BIT_MASK_8_BIT_MIN;
			} else{
				columnOffset = column - columnDrawAreaStart;
				pos = (columnOffset / text->fontPixel) % GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT;
				if(pos >= GRAPHICS_TEXT_FONT_COLUMN_SIZE)
					data[indexData] = GRAPHICS_BIT_MASK_8_BIT_MIN;
				else {
					indexContent = columnOffset / text->fontPixel / GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT;
					indexBitMap = text->content[indexContent] * GRAPHICS_TEXT_FONT_COLUMN_SIZE;
					indexColumnBitMap = indexBitMap + pos;
					columnBitMap = GRAPHICS_ACSII(indexColumnBitMap);
					data[indexData] = GRAPHICS_GET_BIT(columnBitMap, shift, GRAPHICS_TEXT_MASK) == GRAPHICS_TEXT_MASK ? GRAPHICS_BIT_MASK_8_BIT_MAX : GRAPHICS_BIT_MASK_8_BIT_MIN;
				}
			}
			indexData++;
		}
	}
}

static void CalculatorTextDisplaySize(GraphicsTextWidget *text, uint32_t length, uint32_t *columnDisplay, uint32_t *rowDisplay){

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
