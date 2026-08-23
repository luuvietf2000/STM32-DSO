#include "StatusBarVar.h"

//-----------------------------------------------------------------------------------------------------------------//

static char voltagePerDivisionTextContent[VOLTAGE_PER_DIVISION_TEXT_SIZE_CONTENT];
static char timePerDivisionTextContent[TIME_PER_DIVISION_TEXT_SIZE_CONTENT];
static char acquisittionTextContent[ACQUISITION_TEXT_SIZE_CONTENT];
static char zoomScaleTextContent[ZOOM_SCALE_TEXT_SIZE_CONTENT];
static char triggerModeContent[TRIGGER_MODE_TEXT_SIZE_CONTENT];
static char triggerEdgeContent[TRIGGER_EDGE_TEXT_SIZE_CONTENT];
static char triggerLevelContent[TRIGGER_LEVEL_TEXT_SIZE_CONTENT];

const GraphicsTextWidget voltagePerDivisionText = {
	.aligment = VOLTAGE_PER_DIVISION_TEXT_WIDGET_ALIGNMENT,
	.x = VOLTAGE_PER_DIVISION_TEXT_WIDGET_X,
	.y = VOLTAGE_PER_DIVISION_TEXT_WIDGET_Y,
	.width = VOLTAGE_PER_DIVISION_TEXT_WIDGET_WIDTH,
	.height = VOLTAGE_PER_DIVISION_TEXT_WIDGET_HEIGHT,
	.background = VOLTAGE_PER_DIVISION_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = VOLTAGE_PER_DIVISION_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = VOLTAGE_PER_DIVISION_TEXT_WIDGET_FONT_SIZE,
	.content = voltagePerDivisionTextContent
};

const GraphicsTextWidget timePerDivisionText = {
	.aligment = TIME_PER_DIVISION_TEXT_WIDGET_ALIGNMENT,
	.x = TIME_PER_DIVISION_TEXT_WIDGET_X,
	.y = TIME_PER_DIVISION_TEXT_WIDGET_Y,
	.width = TIME_PER_DIVISION_TEXT_WIDGET_WIDTH,
	.height = TIME_PER_DIVISION_TEXT_WIDGET_HEIGHT,
	.background = TIME_PER_DIVISION_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = TIME_PER_DIVISION_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = TIME_PER_DIVISION_TEXT_WIDGET_FONT_SIZE,
	.content = timePerDivisionTextContent
};

const GraphicsTextWidget acquisittionStatusText  = {
	.aligment = ACQUISITTION_STATUS_TEXT_WIDGET_ALIGNMENT,
	.x = ACQUISITTION_STATUS_TEXT_WIDGET_X,
	.y = ACQUISITTION_STATUS_TEXT_WIDGET_Y,
	.width = ACQUISITTION_STATUS_TEXT_WIDGET_WIDTH,
	.height = ACQUISITTION_STATUS_TEXT_WIDGET_HEIGHT,
	.background = ACQUISITTION_STATUS_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = ACQUISITTION_STATUS_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = ACQUISITTION_STATUS_TEXT_WIDGET_FONT_SIZE,
	.content = acquisittionTextContent
};

const GraphicsTextWidget zoomScaleText  = {
	.aligment = ZOOM_SCALE_TEXT_WIDGET_ALIGNMENT,
	.x = ZOOM_SCALE_TEXT_WIDGET_X,
	.y = ZOOM_SCALE_TEXT_WIDGET_Y,
	.width = ZOOM_SCALE_TEXT_WIDGET_WIDTH,
	.height = ZOOM_SCALE_TEXT_WIDGET_HEIGHT,
	.background = ZOOM_SCALE_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = ZOOM_SCALE_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = ZOOM_SCALE_TEXT_WIDGET_FONT_SIZE,
	.content = zoomScaleTextContent
};

const GraphicsTextWidget triggerModeText = {
	.aligment = TRIGGER_MODE_TEXT_WIDGET_ALIGNMENT,
	.x = TRIGGER_MODE_TEXT_WIDGET_X,
	.y = TRIGGER_MODE_TEXT_WIDGET_Y,
	.width = TRIGGER_MODE_TEXT_WIDGET_WIDTH,
	.height = TRIGGER_MODE_TEXT_WIDGET_HEIGHT,
	.background = TRIGGER_MODE_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = TRIGGER_MODE_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = TRIGGER_MODE_TEXT_WIDGET_FONT_SIZE,
	.content = triggerModeContent
};

const GraphicsTextWidget triggerEdgeText = {
	.aligment = TRIGGER_EDGE_TEXT_WIDGET_ALIGNMENT,
	.x = TRIGGER_EDGE_TEXT_WIDGET_X,
	.y = TRIGGER_EDGE_TEXT_WIDGET_Y,
	.width = TRIGGER_EDGE_TEXT_WIDGET_WIDTH,
	.height = TRIGGER_EDGE_TEXT_WIDGET_HEIGHT,
	.background = TRIGGER_EDGE_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = TRIGGER_EDGE_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = TRIGGER_EDGE_TEXT_WIDGET_FONT_SIZE,
	.content = triggerEdgeContent
};

const GraphicsTextWidget triggerLevelText = {
	.aligment = TRIGGER_LEVEL_TEXT_WIDGET_ALIGNMENT,
	.x = TRIGGER_LEVEL_TEXT_WIDGET_X,
	.y = TRIGGER_LEVEL_TEXT_WIDGET_Y,
	.width = TRIGGER_LEVEL_TEXT_WIDGET_WIDTH,
	.height = TRIGGER_LEVEL_TEXT_WIDGET_HEIGHT,
	.background = TRIGGER_LEVEL_TEXT_WIDGET_BACKGROUND_COLOR,
	.textColor = TRIGGER_LEVEL_TEXT_WIDGET_FONT_COLOR,
	.fontPixel = TRIGGER_LEVEL_TEXT_WIDGET_FONT_SIZE,
	.content = triggerLevelContent
};
//-----------------------------------------------------------------------------------------------------------------//

