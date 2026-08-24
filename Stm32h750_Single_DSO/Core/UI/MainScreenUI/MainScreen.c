#include "MainScreen.h"
#include "GraphicsRectangleWidget.h"

//----------------------------------------------------------------------------------------------------------//
#define MAIN_SCREEN_UPDATE_IF_CHANGED(field, target, func)                  \
    do {                                                 					\
        if (field != target){ 												\
            func(field);            										\
        }                                                					\
    } while (0)
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

void MeasurementBarRequestChanged(MeasurementBarConfig *measurementBarParameter){
	MAIN_SCREEN_UPDATE_IF_CHANGED(measurementBarParameter->voltageMax,
	                              measurementBarConfig.voltageMax,
	                              SetVoltageMaxWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(measurementBarParameter->voltageMin,
	                              measurementBarConfig.voltageMin,
	                              SetVoltageMinWidget);
	measurementBarConfig = *measurementBarParameter;
}

void StatusBarRequestChanged(StatusBarConfig *statusBarParameter){
	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->time,
	                              statusBarConfig.time,
	                              SetTimePerDivWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->voltage,
	                              statusBarConfig.voltage,
	                              SetVoltagePerDivWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->zoomScale,
	                              statusBarConfig.zoomScale,
	                              SetZoomModeTextWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->triggerMode,
	                              statusBarConfig.triggerMode,
	                              SetTriggerModeWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->aquisittionState,
	                              statusBarConfig.aquisittionState,
	                              SetAcquisittionStatusWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->triggerEdge,
	                              statusBarConfig.triggerEdge,
	                              SetTriggerEdgeWidget);

	MAIN_SCREEN_UPDATE_IF_CHANGED(statusBarParameter->triggerLevel,
	                              statusBarConfig.triggerLevel,
	                              SetTriggerLevelWidget);
	statusBarConfig = *statusBarParameter;
}

void MainScrrenInit(StatusBarConfig *statusBarParameter, MeasurementBarConfig *measurementBarParameter){
	statusBarConfig = *statusBarParameter;
	measurementBarConfig = *measurementBarParameter;
	GraphicsDrawRectangleWidget((GraphicsRectangleWidget*) &background);
	StatusBarInit(statusBarParameter);
	MeasurementBarInit(measurementBarParameter);
	WaveformInit();
}
