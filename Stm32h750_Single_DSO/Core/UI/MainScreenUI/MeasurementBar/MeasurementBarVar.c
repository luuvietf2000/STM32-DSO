#include "MeasurementBarVar.h"
#include "MeasurementBarConfig.h"
#include "GraphicsTextWidget.h"

//----------------------------------------------------------------------------------------------------//
static char voltageMinContent[VOLTAGE_MIN_TEXT_SIZE_CONTENT];
static char voltageMaxContent[VOLTAGE_MAX_TEXT_SIZE_CONTENT];

const GraphicsTextWidget voltageMaxText = {
	.aligment =VOLTAGE_MAX_TEXT_WIDGET_ALIGNMENT,
	.x =VOLTAGE_MAX_TEXT_WIDGET_X,
	.y =VOLTAGE_MAX_TEXT_WIDGET_Y,
	.width =VOLTAGE_MAX_TEXT_WIDGET_WIDTH,
	.height =VOLTAGE_MAX_TEXT_WIDGET_HEIGHT,
	.background =VOLTAGE_MAX_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor =VOLTAGE_MAX_TEXT_WIDGET_FONT_COLOR,
	.fontPixel =VOLTAGE_MAX_TEXT_WIDGET_FONT_SIZE,
	.content = voltageMaxContent
};

const GraphicsTextWidget voltageMinText = {
	.aligment =VOLTAGE_MIN_TEXT_WIDGET_ALIGNMENT,
	.x =VOLTAGE_MIN_TEXT_WIDGET_X,
	.y =VOLTAGE_MIN_TEXT_WIDGET_Y,
	.width =VOLTAGE_MIN_TEXT_WIDGET_WIDTH,
	.height =VOLTAGE_MIN_TEXT_WIDGET_HEIGHT,
	.background =VOLTAGE_MIN_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor =VOLTAGE_MIN_TEXT_WIDGET_FONT_COLOR,
	.fontPixel =VOLTAGE_MIN_TEXT_WIDGET_FONT_SIZE,
	.content = voltageMinContent
};

//----------------------------------------------------------------------------------------------------//
