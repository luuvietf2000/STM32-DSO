#include "StatusBar.h"
#include "GraphicsTextWidget.h"
#include <stdio.h>
#include "string.h"

//-----------------------------------------------------------------------------------------------------------------//
static const char *const acquisittionText[] = {
	ACQUISITTION_STATUS_TEXT_RUNNING_CONTENT,
	ACQUISITTION_STATUS_TEXT_STOPPED_CONTENT
};

static const char *const triggerModeTextState[] = {
	TRIGGER_MODE_TEXT_MODE_AUTO,
	TRIGGER_MODE_TEXT_MODE_NORMAL,
	TRIGGER_MODE_TEXT_MODE_SINGLE
};

static const char *const triggerEdgeTextState[] = {
	TRIGGER_EDGE_TEXT_MODE_RISING,
	TRIGGER_EDGE_TEXT_MODE_FALLING
};

//-----------------------------------------------------------------------------------------------------------------//
static void GetContentValuePerDiv(uint32_t value, char *buffer, uint16_t size, const char *uintText, const char *miniUintText);
static void GetContentVoltagePerDiv(uint32_t value);
static const char *GetContentAcquisittionStatus(AcquisittionState state);
static const char *GetContentTriggerMode(TriggerModeState state);
static const char *GetContentTriggerEdge(TriggerEdgeState state);
static void SetTextWidget(GraphicsTextWidget *widget, const char *text);
static void GetContentTimePerDiv(uint32_t value);;
//-----------------------------------------------------------------------------------------------------------------//

void SetTriggerLevelWidget(uint32_t level){
	char *buffer = triggerLevelText.content;
	strcpy(buffer, TRIGGER_LEVEL_TEXT_CONTENT_START);
	GetContentValuePerDiv(
		level,
		buffer + strlen(buffer),
		TRIGGER_LEVEL_TEXT_SIZE_CONTENT,
		TRIGGER_LEVEL_TEXT_CONTENT_VOLTAGE_UINT,
		TRIGGER_LEVEL_TEXT_CONTENT_MINI_VOLTAGE_UINT
	);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &triggerLevelText);
}

void SetTriggerEdgeWidget(TriggerEdgeState state){
	const char *content = GetContentTriggerEdge(state);
	SetTextWidget((GraphicsTextWidget*) &triggerEdgeText, content);
}

void SetAcquisittionStatusWidget(AcquisittionState state){
	const char *text = GetContentAcquisittionStatus(state);
	SetTextWidget((GraphicsTextWidget*) &acquisittionStatusText, text);
}

void SetTriggerModeWidget(TriggerModeState state){
	const char *content = GetContentTriggerMode(state);
	SetTextWidget((GraphicsTextWidget*) &triggerModeText, content);
}

static void SetTextWidget(GraphicsTextWidget *widget, const char *text){
	strcpy(widget->content, text);
	GraphicsDrawTextWidget(widget);
}

static const char *GetContentTriggerEdge(TriggerEdgeState state){
	return triggerEdgeTextState[state];
}

static const char *GetContentTriggerMode(TriggerModeState state){
	return triggerModeTextState[state];
}

static const char *GetContentAcquisittionStatus(AcquisittionState state){
	return acquisittionText[state];
}

void SetZoomModeTextWidget(uint16_t scale){
	if(scale > ZOOM_SCALE_MAX)
		return;
	snprintf(
	    zoomScaleText.content,
	    ZOOM_SCALE_TEXT_SIZE_CONTENT,
	    "x%03u",
	    scale
	);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &zoomScaleText);
}

void SetTimePerDivWidget(uint32_t value){
	GetContentTimePerDiv(value);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &timePerDivisionText);
}

static void GetContentTimePerDiv(uint32_t value){
	GetContentValuePerDiv(
		value,
		timePerDivisionText.content,
		TIME_PER_DIVISION_TEXT_SIZE_CONTENT,
		TIME_PER_DIVISION_TEXT_MINI_SECOND_UINT,
		TIME_PER_DIVISION_TEXT_MICRO_SECOND_UINT
	);
}

void SetVoltagePerDivWidget(uint32_t value){
	GetContentVoltagePerDiv(value);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &voltagePerDivisionText);
}

static void GetContentVoltagePerDiv(uint32_t value){
	GetContentValuePerDiv(
		value,
		voltagePerDivisionText.content,
		VOLTAGE_PER_DIVISION_TEXT_SIZE_CONTENT,
		VOLTAGE_PER_DIVISION_TEXT_VOLTAGE_UINT,
		VOLTAGE_PER_DIVISION_TEXT_MINI_VOLTAGE_UINT
	);
}

static void GetContentValuePerDiv(uint32_t value, char *buffer, uint16_t size, const char *uintText, const char *miniUintText){
	uint32_t displayValue;
	if (value < STATUS_BAR_LEVEL_UNIT){
	    displayValue = value;
	    snprintf(buffer, size, "%03lu%s", displayValue, miniUintText);
	} else if(value % STATUS_BAR_LEVEL_UNIT == 0){
	    displayValue = value / STATUS_BAR_LEVEL_UNIT;
	    snprintf(buffer, size, "%04lu%s", displayValue, uintText);
	} else{
		float displayFloat = (float) value / STATUS_BAR_LEVEL_UNIT;
		snprintf(buffer, size, "%04.2f%s", displayFloat, uintText);
	}
}
