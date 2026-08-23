#include "MeasurementBar.h"
#include "stdio.h"

//-----------------------------------------------------------------------------------------------------//
static void SetVoltageDisplay(uint32_t value, char* buffer, uint16_t size, const char* keyworkStart);
//-----------------------------------------------------------------------------------------------------//

void SetVoltageMinWidget(uint32_t value){
	SetVoltageDisplay(
		value,
		voltageMinText.content,
		VOLTAGE_MIN_TEXT_SIZE_CONTENT,
		VOLTAGE_MIN_TEXT_START_CONTENT
	);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &voltageMinText);
}

void SetVoltageMaxWidget(uint32_t value){
	SetVoltageDisplay(
		value,
		voltageMaxText.content,
		VOLTAGE_MAX_TEXT_SIZE_CONTENT,
		VOLTAGE_MAX_TEXT_START_CONTENT
	);
	GraphicsDrawTextWidget((GraphicsTextWidget*) &voltageMaxText);
}

static void SetVoltageDisplay(uint32_t value, char* buffer, uint16_t size, const char* keyworkStart){
	if(value < VOLTAGE_LEVEL_UNIT){
		snprintf(buffer, size, "%s%03lu%s", keyworkStart, value, VOLTAGE_TEXT_CONTENT_MINI_VOLTAGE_UINT);
	} else{
		float valueDisplay = (float) value / VOLTAGE_LEVEL_UNIT;
		snprintf(buffer, size, "%s%04.2f%s", keyworkStart, valueDisplay, VOLTAGE_TEXT_CONTENT_VOLTAGE_UINT);
	}
}

