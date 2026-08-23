#ifndef UI_MAINSCREENUI_STATUSBAR_STATICBARCONFIG_H_
#define UI_MAINSCREENUI_STATUSBAR_STATICBARCONFIG_H_

#include <stdint.h>

//-----------------------------------------------------------------------------------------------------------------//
#define VOLTAGE_PER_DIVISION_DEFFAULT																1000
#define TIME_PER_DIVISION_DEFFAULT																	100
//----------------------------------------------------------------------------------------------------//
#define VOLTAGE_PER_DIVISION_TEXT_SIZE_CONTENT														11
#define TIME_PER_DIVISION_TEXT_SIZE_CONTENT															11
#define ACQUISITION_TEXT_SIZE_CONTENT																5
#define ZOOM_SCALE_TEXT_SIZE_CONTENT																7
#define TRIGGER_MODE_TEXT_SIZE_CONTENT																6
#define TRIGGER_EDGE_TEXT_SIZE_CONTENT																8
#define TRIGGER_LEVEL_TEXT_SIZE_CONTENT																11
//----------------------------------------------------------------------------------------------------//
#define STATUS_BAR_LEVEL_UNIT																		1000
#define ACQUISITTION_STATUS_TEXT_RUNNING_CONTENT													"Run"
#define ACQUISITTION_STATUS_TEXT_STOPPED_CONTENT													"Stop"
//----------------------------------------------------------------------------------------------------//
#define ZOOM_SCALE_TEXT_CONTENT																		"x"
#define ZOOM_SCALE_TEXT_DISABLE																		" "
#define ZOOM_SCALE_DEFFAULT																			25
#define ZOOM_SCALE_MAX																				999
//----------------------------------------------------------------------------------------------------//
#define VOLTAGE_PER_DIVISION_TEXT_VOLTAGE_UINT														"V/div"
#define VOLTAGE_PER_DIVISION_TEXT_MINI_VOLTAGE_UINT													"mV/div"
//----------------------------------------------------------------------------------------------------//
#define TIME_PER_DIVISION_TEXT_MINI_SECOND_UINT														"mS/div"
#define TIME_PER_DIVISION_TEXT_MICRO_SECOND_UINT													"uS/div"
//----------------------------------------------------------------------------------------------------//
#define TRIGGER_MODE_TEXT_MODE_DEFFAULT																TRIGGER_AUTO
#define TRIGGER_MODE_TEXT_MODE_AUTO																	"AUTO"
#define TRIGGER_MODE_TEXT_MODE_NORMAL																"NOR "
#define TRIGGER_MODE_TEXT_MODE_SINGLE																"SING"
//----------------------------------------------------------------------------------------------------//
#define TRIGGER_EDGE_TEXT_MODE_DEFFAULT																TRIGGER_RISSING_EDGE
#define TRIGGER_EDGE_TEXT_MODE_RISING																"RISING "
#define TRIGGER_EDGE_TEXT_MODE_FALLING																"FALLING"
//----------------------------------------------------------------------------------------------------/
#define TRIGGER_LEVEL_TEXT_LEVEL_DEFFAULT															1100
#define TRIGGER_LEVEL_TEXT_CONTENT_START															"Trig:"
#define TRIGGER_LEVEL_TEXT_CONTENT_VOLTAGE_UINT														"V"
#define TRIGGER_LEVEL_TEXT_CONTENT_MINI_VOLTAGE_UINT												"mV"
//-----------------------------------------------------------------------------------------------------------------//
#endif /* UI_MAINSCREENUI_STATUSBAR_STATICBARCONFIG_H_ */
