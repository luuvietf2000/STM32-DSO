#include "GraphicsTextWidget.h"
#include "AsciiDeffaultFont.h"
#include "string.h"
#include "GraphicsRectangleWidget.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_TEXT_CALCULATO_POSITIVE_DIFFERENCE(one, two)											(one > two ? one - two : 0)
//----------------------------------------------------------------------------------------------------------//
static void CalculatorTextDisplaySize(GraphicsTextWidget *text, uint32_t length, uint32_t *columnDisplay, uint32_t *rowDisplay);
static void ConvertBitMask8bit(uint8_t *data, char *content, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDisplay, uint32_t rowDisplay);
static void GraphicsRenderTextContent(GraphicsTextWidget *text, char *content, uint32_t bgColor, uint16_t xDisplay, uint16_t yDisplay, uint16_t columnDisplay, uint16_t rowDisplay);
static void GraphicsCalculateTextDisplayPosition(GraphicsTextWidget *text, uint32_t length, uint32_t *xDisplay, uint32_t *yDisplay, uint32_t *columnDisplay, uint32_t *rowDisplay);
//----------------------------------------------------------------------------------------------------------//


void GraphicsDrawTextWidget(GraphicsTextWidget *text){
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
		text->content,
		text->background,
		xDisplay,
		yDisplay,
		columnDisplay,
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

static void GraphicsRenderTextContent(GraphicsTextWidget *text, char *content, uint32_t bgColor, uint16_t xDisplay, uint16_t yDisplay, uint16_t columnDisplay, uint16_t rowDisplay){
    if(rowDisplay == 0 || columnDisplay == 0)
        return;
    GraphicsSetAreaRequest(
        xDisplay,
        xDisplay + columnDisplay,
        yDisplay,
        yDisplay + rowDisplay
    );
    GraphicsSetMode(GRAPHICS_DMA2D_MODE_BLEND_BG);
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
			content,
            text,
            i,
            columnDisplay,
            row
        );

        GraphicsConvertColors(
            text->textColor,
            bgColor,
            buffer,
            data,
            size / GRAPHICS_PIXEL_PER_BYTE,
            1
        );
        GraphicsTransfer( data, size, GRAPHICS_TEXT_TRANSFER_COUNT);
    }
}
void GraphicsTextWidgetSetText(GraphicsTextWidget *text, char *content){
	GraphicsTextWidgetUpdateContent(text, text->content, content, text->background);
	strcpy(text->content, content);
}

void GraphicsTextWidgetUpdateContent(GraphicsTextWidget *text, char *textOld, char *textNew, uint32_t newBgColor){
	uint32_t row, column;
	uint32_t columnDisplayNew, rowDisplayNew;
	uint32_t xDisplayNew, yDisplayNew;

	uint32_t lengthNew = strlen(textNew);
	uint32_t lengthOld = strlen(textOld);
	uint32_t lengthMax = GRAPHICS_GET_MAX(lengthNew, lengthOld);
	uint32_t xDisplay, yDisplay;
	GraphicsCalculateTextDisplayPosition(text, lengthMax, &xDisplay, &yDisplay, &column, &row);
	GraphicsCalculateTextDisplayPosition(text, lengthNew, &xDisplayNew, &yDisplayNew, &columnDisplayNew, &rowDisplayNew);

	if(columnDisplayNew < column){
		GraphicsRectangleWidget rectangle;
		if(xDisplay < xDisplayNew){
			GraphicsRectangleSetParameter(
				&rectangle,
				xDisplay,
				yDisplay,
				xDisplayNew - xDisplay,
				row,
				text->background,
				0x00,
				0
			);
			GraphicsDrawRectangleWidget(&rectangle);
		}
		if(xDisplayNew + columnDisplayNew < xDisplay + column){
			GraphicsRectangleSetParameter(
				&rectangle,
				xDisplayNew + columnDisplayNew,
				yDisplay,
				(xDisplay + column) - (xDisplayNew + columnDisplayNew),
				row,
				text->background,
				0x00,
				0
			);
			GraphicsDrawRectangleWidget(&rectangle);
		}
	}

	GraphicsRenderTextContent(
		text,
		textNew,
		newBgColor,
		xDisplayNew,
		yDisplayNew,
		columnDisplayNew,
		rowDisplayNew
	);

}


static void ConvertBitMask8bit(uint8_t *data, char* content, GraphicsTextWidget *text, uint32_t rowCurrent, uint32_t columnDisplay, uint32_t rowDisplay){
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
				indexBitMap = content[indexContent] * GRAPHICS_TEXT_FONT_COLUMN_SIZE;
				indexColumnBitMap = indexBitMap + pos;
				columnBitMap = GRAPHICS_ACSII(indexColumnBitMap);
				data[indexData] = GRAPHICS_GET_BIT(columnBitMap, shift, GRAPHICS_TEXT_MASK) == GRAPHICS_TEXT_MASK ? GRAPHICS_BIT_MASK_8_BIT_MAX : GRAPHICS_BIT_MASK_8_BIT_MIN;
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
