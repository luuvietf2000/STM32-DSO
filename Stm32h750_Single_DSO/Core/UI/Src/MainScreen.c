#include "Graphics.h"
#include "MainScreen.h"
#include "string.h"
#include "StatusBarConfig.h"
#include "MeasurementBarConfig.h"
#include "WaveformConfig.h"
//------------------------------------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------------------------//
HAL_StatusTypeDef MainScreenInit(){
	HAL_StatusTypeDef result = HAL_OK;

	result |= GraphicsDrawRectangleWidget(&mainScreen);
	result |= StatusBarInit();
	result |= MeasurementBarInit();
	WaveformWidgetInit();
	return result;
}


