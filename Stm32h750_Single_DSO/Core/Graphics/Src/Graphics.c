#include "Graphics.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "stm32h7xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "cmsis_os2.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_LEFT(parent, child)										0
#define GRAPHICS_CENTER(parent, child)										((parent - child) / 2)
#define GRAPHICS_RIGHT(parent, child)										(parent - child)
//----------------------------------------------------------------------------------------------------------//
static void Dma2dTransferCompleteCallback(DMA2D_HandleTypeDef *ptr);
static void GraphicsSleepTask();
static void GraphicsSetDma2dModeBlendBg(GraphicsDma2dClutMode mode);
static void GraphicsSetDma2dModeFill();
static uint32_t GraphicsSwapByte(uint32_t color);
//----------------------------------------------------------------------------------------------------------//
__attribute__((section(".dma_buffer")))
uint8_t graphicsBuffer[GRAPHICS_BUFFER_SIZE];
static DMA2D_HandleTypeDef *graphicsDma2d;
static StaticSemaphore_t semaphoreBuffer;
static SemaphoreHandle_t graphicsSemaphore;
//----------------------------------------------------------------------------------------------------------//
void GraphicsDma2dSetOffsetPixel(uint32_t size){
	if(graphicsDma2d->Init.OutputOffset == 0)
		return;
	CLEAR_BIT(graphicsDma2d->Instance->CR, DMA2D_CR_LOM);
	MODIFY_REG(graphicsDma2d->Instance->OOR, DMA2D_OOR_LO, size);
}
static uint32_t GraphicsSwapByte(uint32_t color){
	uint32_t red = color & GRAPHICS_RGB888_RED;
	uint32_t green = color & GRAPHICS_RGB888_GREEN;
	uint32_t blue = color & GRAPHICS_RGB888_BLUE;
    uint16_t rgb565 = GRAPHICS_CONVERT_COLOR(red, green, blue);
	return GRAPHICS_SWAP_BYTE(rgb565);
}
void GraphicsDma2dFillModeStart(uint32_t height, uint32_t width, uint8_t *address, uint32_t color){
	  MODIFY_REG(graphicsDma2d->Instance->NLR, (DMA2D_NLR_NL | DMA2D_NLR_PL), (height | (width << DMA2D_NLR_PL_Pos)));
	  WRITE_REG(graphicsDma2d->Instance->OMAR, (uint32_t) address);
	  WRITE_REG(
		  graphicsDma2d->Instance->OCOLR,
		  GraphicsSwapByte(color)
	  );
	__HAL_DMA2D_ENABLE_IT(graphicsDma2d, DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE);
	__HAL_DMA2D_ENABLE(graphicsDma2d);
	GraphicsSleepTask();
}

void GraphicsSetManualClutBg(uint32_t *color, uint32_t size){
    volatile uint32_t *clut = (volatile uint32_t *)graphicsDma2d->Instance->BGCLUT;
    for (uint32_t i = 0; i < size; i++){
        clut[i] = color[i];
    }
}

void GraphicsSetMode(GraphicsDma2dMode mode){
	switch(mode){
		case GRAPHICS_DMA2D_MODE_FILL_COLOR:
			GraphicsSetDma2dModeFill();
			break;
		case GRAPHICS_DMA2D_MODE_BLEND_BG:
			GraphicsSetDma2dModeBlendBg(GRAPHICS_DMA2D_NOT_USING_CLUT);
			break;
		case GRAPHICS_DMA2D_MODE_BLEND_CLUT_BG:
			GraphicsSetDma2dModeBlendBg(GRAPHICS_DMA2D_USING_CLUT);
			break;
		default:
			break;
	}
}

void GraphicsDrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color){
	GraphicsSetMode(GRAPHICS_DMA2D_MODE_FILL_COLOR);
	GraphicsDma2dSetOffsetPixel(0);
	GraphicsSetAreaRequest(
		x,
		x + width,
		y,
		y + height
	);
	uint32_t prefecrredSize = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(width, height));
	uint32_t fallbackSize = GRAPHICS_GET_MAX(width, height) * GRAPHICS_PIXEL_PER_BYTE;
	uint8_t *data = NULL;
	uint32_t size = GraphicsGetPointerMemory(&data, prefecrredSize, fallbackSize);
	GraphicsDma2dFillModeStart(size / GRAPHICS_PIXEL_PER_BYTE, 1, data, color);
	uint32_t transferCount = prefecrredSize / size;
	GraphicsTransfer(data, size, transferCount);
}


static void GraphicsSetDma2dModeFill(){
	if(graphicsDma2d->Init.Mode == DMA2D_R2M)
		return;
	graphicsDma2d->Init.Mode = DMA2D_R2M;
	MODIFY_REG(graphicsDma2d->Instance->CR, DMA2D_CR_MODE, DMA2D_R2M);
	graphicsDma2d->Init.ColorMode = DMA2D_OUTPUT_RGB565;
	MODIFY_REG(graphicsDma2d->Instance->OPFCCR, DMA2D_OPFCCR_CM, DMA2D_OUTPUT_RGB565);
	graphicsDma2d->Init.LineOffsetMode = 0;
	MODIFY_REG(graphicsDma2d->Instance->OOR, DMA2D_OOR_LO, 0);
}

static void GraphicsSetDma2dModeBlendBg(GraphicsDma2dClutMode mode){
	if(graphicsDma2d->Init.Mode == DMA2D_M2M_BLEND_BG)
		return;
	graphicsDma2d->Init.Mode = DMA2D_M2M_BLEND_BG;
	MODIFY_REG(graphicsDma2d->Instance->CR, DMA2D_CR_MODE, DMA2D_M2M_BLEND_BG);
	MODIFY_REG(graphicsDma2d->Instance->OPFCCR, DMA2D_OPFCCR_CM, DMA2D_OUTPUT_RGB565);
	MODIFY_REG(graphicsDma2d->Instance->FGPFCCR, DMA2D_FGPFCCR_CM | DMA2D_FGPFCCR_AM, mode | DMA2D_NO_MODIF_ALPHA);
	MODIFY_REG(graphicsDma2d->Instance->FGOR, DMA2D_FGOR_LO, 0);
}

void GraphiscsSetAlignment(GraphicsAlignment alignment, uint32_t columnParent, uint32_t rowParent, uint32_t columnChild, uint32_t rowChild, uint32_t xSet, uint32_t ySet, uint32_t *xDisplay, uint32_t *yDisplay){
	uint32_t x, y;
	switch (alignment) {
		case GRAPHICS_ALIGNMENT_TOP_LEFT:
			x = GRAPHICS_LEFT(columnParent, columnChild);
			y = GRAPHICS_LEFT(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_TOP_CENTER:
			x = GRAPHICS_CENTER(columnParent, columnChild);
			y = GRAPHICS_LEFT(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_TOP_RIGHT:
			x = GRAPHICS_RIGHT(columnParent, columnChild);
			y = GRAPHICS_LEFT(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_MIDDLE_LEFT:
			x = GRAPHICS_LEFT(columnParent, columnChild);
			y = GRAPHICS_CENTER(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_CENTER:
			x = GRAPHICS_CENTER(columnParent, columnChild);
			y = GRAPHICS_CENTER(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_MIDDLE_RIGHT:
			x = GRAPHICS_RIGHT(columnParent, columnChild);
			y = GRAPHICS_CENTER(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_BOTTOM_LEFT:
			x = GRAPHICS_LEFT(columnParent, columnChild);
			y = GRAPHICS_RIGHT(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_BOTTOM_CENTER:
			x = GRAPHICS_CENTER(columnParent, columnChild);
			y = GRAPHICS_RIGHT(rowParent, rowChild);
			break;
		case GRAPHICS_ALIGNMENT_BOTTOM_RIGHT:
			x = GRAPHICS_RIGHT(columnParent, columnChild);
			y = GRAPHICS_RIGHT(rowParent, rowChild);
			break;
		default:
			x = 0;
			y = 0;
			break;
	}
	*xDisplay = x + xSet;
	*yDisplay = y + ySet;
}

void GraphicsConvertColors(uint32_t foreground, uint32_t background, uint8_t *bitMask, uint8_t *destination, uint32_t width, uint32_t height){
	WRITE_REG(graphicsDma2d->Instance->FGCOLR, foreground);
	WRITE_REG(graphicsDma2d->Instance->BGCOLR, background);
	MODIFY_REG(graphicsDma2d->Instance->NLR, (DMA2D_NLR_NL | DMA2D_NLR_PL), (height | (width << DMA2D_NLR_PL_Pos)));
	WRITE_REG(graphicsDma2d->Instance->OMAR, (uint32_t) destination);
	WRITE_REG(graphicsDma2d->Instance->FGMAR, bitMask);
	__HAL_DMA2D_ENABLE_IT(graphicsDma2d, DMA2D_IT_TC | DMA2D_IT_TE | DMA2D_IT_CE);
	__HAL_DMA2D_ENABLE(graphicsDma2d);
	GraphicsSleepTask();

}

void GraphicsInit(DMA2D_HandleTypeDef *dma2d){
	graphicsDma2d = dma2d;
	graphicsSemaphore = xSemaphoreCreateBinaryStatic(&semaphoreBuffer);
	graphicsDma2d->XferCpltCallback = Dma2dTransferCompleteCallback;
}

static void Dma2dTransferCompleteCallback(DMA2D_HandleTypeDef *ptr){
	if(graphicsDma2d == ptr){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(graphicsSemaphore, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

static void GraphicsSleepTask(){
	xSemaphoreTake(graphicsSemaphore, portMAX_DELAY);
}

