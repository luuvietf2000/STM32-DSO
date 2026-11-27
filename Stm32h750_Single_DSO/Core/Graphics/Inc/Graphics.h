#ifndef GRAPHICS_INC_GRAPHICS_H_
#define GRAPHICS_INC_GRAPHICS_H_

#include "stm32h7xx_hal.h"
#include "GraphicsConf.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_COLOR_BYTE																	8
#define GRAPHICS_SET_RGB888(red, green, blue) 												(((uint32_t)(red) << 16U) | ((uint32_t)(green) << 8U) | (uint32_t)(blue))
#if(GRAPHICS_RGB_FORMAT == GRAPHICS_RGB565_FORMAT)
	#define GRAPHICS_SET_COLOR(red, green, blue)											((red << (GRAPHICS_COLOR_RED * GRAPHICS_COLOR_BYTE)\
																							| green << (GRAPHICS_COLOR_GREEN * GRAPHICS_COLOR_BYTE) \
																							| blue << (GRAPHICS_COLOR_BLUE * GRAPHICS_COLOR_BYTE)))
	#define GRAPHICS_PIXEL_PER_BYTE															2
	#define GRAPHICS_CONVERT_COLOR(red, green, blue)										(((red >> 19U) << 11U) | ((green >> 10U) << 5U) | (blue >> 3U))
	#define GRAPHICS_SWAP_BYTE(color)														((uint16_t)((color >> 8U) | (color << 8U)))
#endif
#define GRAPHICS_RGB888_RED																	0xFF0000
#define GRAPHICS_RGB888_GREEN     															0x00FF00U
#define GRAPHICS_RGB888_BLUE      															0x0000FFU
#define GRAPHICS_GET_PIXEL(column, row)														(column * row)
#define GRAPHICS_GET_PIXEL_BYTE(size)														(size * GRAPHICS_PIXEL_PER_BYTE)
#define GRAPHICS_GET_MAX(one, two)															(one > two ? one : two)
#define GRAPHICS_GET_MIN(one, two)															(one > two ? two : one)
#define GRAPHICS_GET_BIT(value, shift, mask)												((value >> shift) & mask)
#define GRAPHICS_RGB888_RED_COLOR_MASK														0xFF0000
#define GRAPHICS_RGB888_GREEN_COLOR_MASK													0x00FF00
#define GRAPHICS_RGB888_BLUE_COLOR_MASK														0x0000FF
#define GRAPHICS_ALIGN_TO_4(x)																(x % 4 == 0 ? x : x + GRAPHICS_PIXEL_PER_BYTE)
#define GRAPHICS_CEIL_UP(size, up)															(size % up == 0 ? 0 : 1)
#define GRAPHICS_ONE_PIXEL																	1
//----------------------------------------------------------------------------------------------------------//
typedef enum
{
    GRAPHICS_COLOR_BLUE,
    GRAPHICS_COLOR_GREEN,
    GRAPHICS_COLOR_RED
} GraphicsColorFormatEnum;

typedef enum {
    GRAPHICS_ALIGNMENT_TOP_LEFT,
    GRAPHICS_ALIGNMENT_TOP_CENTER,
    GRAPHICS_ALIGNMENT_TOP_RIGHT,

    GRAPHICS_ALIGNMENT_MIDDLE_LEFT,
    GRAPHICS_ALIGNMENT_CENTER,
    GRAPHICS_ALIGNMENT_MIDDLE_RIGHT,

    GRAPHICS_ALIGNMENT_BOTTOM_LEFT,
    GRAPHICS_ALIGNMENT_BOTTOM_CENTER,
    GRAPHICS_ALIGNMENT_BOTTOM_RIGHT,
} GraphicsAlignment;

typedef enum{
	GRAPHICS_DMA2D_MODE_FILL_COLOR							= DMA2D_R2M,
	GRAPHICS_DMA2D_MODE_BLEND_BG							= DMA2D_M2M_BLEND_BG,
	GRAPHICS_DMA2D_MODE_BLEND_CLUT_BG
} GraphicsDma2dMode;

typedef enum{
	GRAPHICS_DMA2D_USING_CLUT                               = DMA2D_INPUT_L8,
	GRAPHICS_DMA2D_NOT_USING_CLUT							= DMA2D_INPUT_A8
} GraphicsDma2dClutMode;

typedef enum {
    GRAPHICS_DMA2D_OUTPUT_SWAP_BYTE_DISABLE = 0,
    GRAPHICS_DMA2D_OUTPUT_SWAP_BYTE_ENABLE
} GraphicsDma2dOutputSwapByte;
//----------------------------------------------------------------------------------------------------------//

typedef struct{
	uint32_t start;
	uint32_t end;
} GraphicsPoint;

//----------------------------------------------------------------------------------------------------------//
extern void GraphicsSetRowRequest(uint16_t rowStart, uint16_t rowEnd);
extern void GraphicsSetAreaRequest(uint16_t columnStart, uint16_t columnEnd, uint16_t rowStart, uint16_t rowEnd);
extern uint32_t GraphicsGetPointerMemory(uint8_t **data, uint32_t preferredSize, uint32_t faillbackSize);
void GraphicsTransfer(uint8_t *data, uint32_t dataSize, uint32_t transferCount);
//------------------------------------------------------------------------------------//
void GraphicsDma2dSetOffsetPixel(uint32_t size);
void GraphicsDma2dFillModeStart(uint32_t height, uint32_t width, uint8_t *address, uint32_t color);
void GraphicsSetManualClutBg(uint32_t *color, uint32_t size);
void GraphicsSetMode(GraphicsDma2dMode mode);
void GraphicsDrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
void GraphicsConvertColors(uint32_t foreground, uint32_t background, uint8_t *bitMask, uint8_t *destination, uint32_t width, uint32_t height);
void GraphicsInit(DMA2D_HandleTypeDef *dma2d);
void GraphicsFillColor(uint32_t color, uint8_t *address, uint32_t size);
void GraphicsSetAlignment(GraphicsAlignment alignment, uint32_t columnParent, uint32_t rowParent, uint32_t columnChild, uint32_t rowChild, uint32_t xSet, uint32_t ySet, uint32_t *xDisplay, uint32_t *yDisplay);
//----------------------------------------------------------------------------------------------------------//
#endif /* GRAPHICS_INC_GRAPHICS_H_ */
