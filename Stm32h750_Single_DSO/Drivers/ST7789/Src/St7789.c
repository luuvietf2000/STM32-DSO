#include "St7789.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include "semphr.h"

//-----------------------------------------------------------------------------------------------------//
static St7789Config config;
static StaticSemaphore_t semaphoreBuffer;
static SemaphoreHandle_t semaphore;
//-----------------------------------------------------------------------------------------------------//
static void St7789SetAddress(uint8_t cmd, uint16_t start, uint16_t end);
static HAL_StatusTypeDef St7789WriteCommand(uint8_t command);
//-----------------------------------------------------------------------------------------------------//
static void St7789SetAddress(uint8_t cmd, uint16_t start, uint16_t end){
	const uint8_t mask = 0xFF;
	const uint8_t shift = 0x08;

	uint8_t parameter[] = {
		ST7789_GET_FIELD(start, shift, mask),
		ST7789_GET_FIELD(start, 0, mask),
		ST7789_GET_FIELD(end, shift, mask),
		ST7789_GET_FIELD(end, 0, mask)
	};
	St7789WriteCommand(cmd);
	#if (ST7789_D_CACHE_MODE == ST7789_USING_D_CACHE)
		HAL_SPI_Transmit(config.spi, parameter, 4, portMAX_DELAY);
	#else
		SCB_CleanInvalidateDCache_by_Addr((uint32_t*) parameter, sizeof(parameter));
		St7789WriteData(parameter, sizeof(parameter));
	#endif
}


static HAL_StatusTypeDef St7789WriteCommand(uint8_t command){
	ST7789_PIN_LOW(config.dc);
	HAL_StatusTypeDef result = HAL_SPI_Transmit(config.spi, &command, sizeof(uint8_t), portMAX_DELAY);
	ST7789_PIN_HIGH(config.dc);
	return result;
}

HAL_StatusTypeDef St7789WriteData(uint8_t *data, uint32_t size){
	HAL_StatusTypeDef result = HAL_SPI_Transmit_DMA(config.spi, data, size);
    if (result != HAL_OK){
        return result;
    }
    xSemaphoreTake(semaphore, portMAX_DELAY);
	return result;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){
	if(hspi == config.spi){
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(semaphore, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

void St7789RstHardware(){
	ST7789_PIN_LOW(config.rst);
	HAL_Delay(ST7789_RST_HARDWARE_TIME);
	ST7789_PIN_HIGH(config.rst);
	HAL_Delay(ST7789_RST_HARDWARE_TIME);
}

void St7789RstSoftware(){
	St7789WriteCommand(ST7789_CMD_SWRESET);
	HAL_Delay(ST7789_RST_SOFTWARE_TIME);
}

void St7789SetInterfacePixelFormat(St7789ControlInterfaceColorFormat control, St7789RgbInterfaceColorFormat rgb){
	uint8_t parameter = 0;
	parameter |= ST7789_FIELD(control, ST7789_CONTROL_INTERFACE_COLOR_FORMAT_S, ST7789_CONTROL_INTERFACE_COLOR_FORMAT_M);
	parameter |= ST7789_FIELD(rgb, ST7789_RGB_INTERFACE_COLOR_FORMAT_S, ST7789_RGB_INTERFACE_COLOR_FORMAT_M);
	St7789WriteCommand(ST7789_CMD_COLMOD);
	#if (ST7789_D_CACHE_MODE == ST7789_USING_D_CACHE)
		HAL_SPI_Transmit(config.spi, &parameter, 1, portMAX_DELAY);
	#else
		SCB_CleanInvalidateDCache_by_Addr((uint32_t*) &parameter, 1);
		St7789WriteData(&parameter, 1);
	#endif
}

void St7789SetSleepMode(St7789SleepMode mode){
	switch(mode){
		case ST7789_SLEEP_MODE_IN:
			St7789WriteCommand(ST7789_CMD_SLPIN);
			break;
		case ST7789_SLEEP_MODE_OUT:
			St7789WriteCommand(ST7789_CMD_SLPOUT);
			break;
	}
	HAL_Delay(ST7789_SLEEP_MODE_DELAY_TIME);
}

void St7789Init(St7789Config *_config){
	semaphore = xSemaphoreCreateBinaryStatic(&semaphoreBuffer);

	config = *_config;

	St7789RstHardware();

	St7789SetInterfacePixelFormat(config.format, RGB_INTERFACE_262K);

	St7789WriteCommand(ST7789_CMD_INVOFF);

	St7789SetSleepMode(ST7789_SLEEP_MODE_OUT);

	St7789SetMemoryDataAccessControl();

	St7789WriteCommand(ST7789_CMD_NORON);

	St7789WriteCommand(St7789_CMD_DISON);

}

void St7789SetMemoryDataAccessControl(){
	// color format: RGB
	// refresh: top -> bot, left -> right
	uint16_t pixel;
	switch (config.rotate) {
		case ST7789_DISPLAY_NORMAL:
		case ST7789_DISPLAY_INVERTED:
			break;
		case ST7789_DISPLAY_RIGHT:
		case ST7789_DISPLAY_LEFT:
			pixel = config.size.row;
			config.size.row = config.size.column;
			config.size.column = pixel;
			break;
	}
	St7789WriteCommand(ST7789_CMD_MADCPL);
	#if (ST7789_D_CACHE_MODE == ST7789_USING_D_CACHE)
		HAL_SPI_Transmit(config.spi, &config.rotate, 1, portMAX_DELAY);
	#else
		SCB_CleanInvalidateDCache_by_Addr((uint32_t*) &config.rotate, 1);
		St7789WriteData(&config.rotate, 1);
	#endif
}

void St7789SetColumnAddress(uint16_t start, uint16_t end){
	St7789SetAddress(ST7789_CMD_CASET, start, end - ST7789_PIXEL);
}

void St7789SetRowAddress(uint16_t start, uint16_t end){
	St7789SetAddress(ST7789_CMD_RASET, start, end - ST7789_PIXEL);
}

void St7789RequestStartTransferData(){
	St7789WriteCommand(ST7789_CMD_RAMWR);
}

void St7789ConvertFor18bit(uint8_t *ptr, St7789RgbColor *rgb, const uint8_t *shift){
	for(St7789ColorDeffault i = 0; i < ST7789_COLOR_DEFFAULT_SIZE_BYTE; i++){
		uint8_t color = ST7789_CONVERT_8BIT_TO_NBIT(ST7789_6_BIT_COLOR, rgb->color[i]) << *shift;
		*(ptr + i) = color;
	}
}

void St7789ConvertFor16bit(uint8_t *ptr, St7789RgbColor *rgb){
	uint8_t greenAfterConvert = ST7789_CONVERT_8BIT_TO_NBIT(ST7789_6_BIT_COLOR, rgb->color[ST7789_GREEN_COLOR_DEFFAULT]);
	*(ptr) = ST7789_CONVERT_8BIT_TO_NBIT(ST7789_5_BIT_COLOR, rgb->color[ST7789_RED_COLOR_DEFFAULT]) << ST7789_RGB_COLOR_MODE_16_BIT_RED_SHIFT |
			ST7789_GET_FIELD(greenAfterConvert, ST7789_RGB_COLOR_MODE_16_BIT_GREEN_SHIFT_PART_HIGH, ST7789_RGB_COLOR_MODE_16_BIT_GREEN_MASK_PART_HIGH);
	*(ptr + 1) = ST7789_CONVERT_8BIT_TO_NBIT(ST7789_5_BIT_COLOR, rgb->color[ST7789_BLUE_COLOR_DEFFAULT]) << ST7789_RGB_COLOR_MODE_16_BIT_BLUE_SHIFT |
			(ST7789_GET_FIELD(greenAfterConvert, ST7789_RGB_COLOR_MODE_16_BIT_GREEN_SHIFT_PART_LOW, ST7789_RGB_COLOR_MODE_16_BIT_GREEN_MASK_PART_HIGH) << ST7789_RGB_COLOR_MODE_16_BIT_GREEN_SHIFT_BYTE_LOW);
}




