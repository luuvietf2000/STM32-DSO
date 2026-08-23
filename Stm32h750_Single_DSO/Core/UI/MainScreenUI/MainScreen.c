#include "MainScreen.h"
#include "GraphicsRectangleWidget.h"

//----------------------------------------------------------------------------------------------------------//
static const GraphicsRectangleWidget background = {
	.x = MAIN_SCREEN_X,
	.y = MAIN_SCREEN_Y,
	.width = MAIN_SCREEN_WIDTH,
	.height = MAIN_SCREEN_HEIGHT,
	.borderWidth = MAIN_SCREEN_OUTLINE,
	.borderColor = MAIN_SCREEN_BACKGROUND_COLOR,
	.color = MAIN_SCREEN_BACKGROUND_COLOR
};

static StatusBarConfig statusBarConfig;
static MeasurementBarConfig measurementBarConfig;
//----------------------------------------------------------------------------------------------------------//
static void StatusBarInit(StatusBarConfig *statusBarParameter);

//----------------------------------------------------------------------------------------------------------//

static void MeasurementBarInit(MeasurementBarConfig *measurementBarParameter){
	SetVoltageMaxWidget(measurementBarParameter->voltageMax);
	SetVoltageMinWidget(measurementBarParameter->voltageMin);
}

static void StatusBarInit(StatusBarConfig *statusBarParameter){
	SetTimePerDivWidget(statusBarParameter->time);
	SetVoltagePerDivWidget(statusBarParameter->voltage);
	SetZoomModeTextWidget(statusBarParameter->zoomScale);
	SetTriggerModeWidget(statusBarParameter->triggerMode);
	SetAcquisittionStatusWidget(statusBarParameter->aquisittionState);
	SetTriggerEdgeWidget(statusBarParameter->triggerEdge);
	SetTriggerLevelWidget(statusBarParameter->triggerLevel);
}

void MainScrrenInit(StatusBarConfig *statusBarParameter, MeasurementBarConfig *measurementBarParameter){
	statusBarConfig = *statusBarParameter;
	measurementBarConfig = *measurementBarParameter;
	GraphicsDrawRectangleWidget((GraphicsRectangleWidget*) &background);
	StatusBarInit(statusBarParameter);
	MeasurementBarInit(measurementBarParameter);
	WaveformInit();
}
