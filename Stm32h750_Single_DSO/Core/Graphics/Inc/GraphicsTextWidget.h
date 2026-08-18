#ifndef GRAPHICS_INC_GRAPHICSTEXTWIDGET_H_
#define GRAPHICS_INC_GRAPHICSTEXTWIDGET_H_

#include "Graphics.h"

//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_TEXT_FONT_COLUMN_SIZE										FONT_DEFFAULT_COLUMN
#define GRAPHICS_TEXT_FONT_ROW_SIZE											FONT_DEFFAULT_ROW
#define GRAPHICS_TEXT_COLUMN_SIZE_DEFFAULT									(GRAPHICS_TEXT_FONT_COLUMN_SIZE + GRAPHICS_PIXEL_SPACE)
#define GRAPHICS_TEXT_ROW_SIZE_DEFFAULT										(GRAPHICS_TEXT_FONT_ROW_SIZE + GRAPHICS_PIXEL_SPACE)
#define GRAPHICS_ACSII(x)													(asciiBitMap[x])
#define GRAPHICS_BIT_MASK_8_BIT_MAX											0xFF
#define GRAPHICS_BIT_MASK_8_BIT_MIN											0
#define GRAPHICS_TEXT_MASK													0x01
#define GRAPHICS_TEXT_TRANSFER_COUNT										1
//----------------------------------------------------------------------------------------------------------//
typedef struct{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	char *content;
	GraphicsAlignment aligment;
	uint32_t textColor;
	uint32_t background;
	uint32_t fontPixel;
} GraphicsTextWidget;
//----------------------------------------------------------------------------------------------------------//
extern uint8_t graphicsBuffer[GRAPHICS_BUFFER_SIZE];
//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawTextWidget(GraphicsTextWidget *text);

#endif /* GRAPHICS_INC_GRAPHICSTEXTWIDGET_H_ */
