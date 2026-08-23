#ifndef UI_MAINSCREEN_INC_MAINSCREENLAYOUT_H_
#define UI_MAINSCREEN_INC_MAINSCREENLAYOUT_H_

#include "LayoutMacro.h"

//----------------------------------------------------------------------------------------------------------//

#define MAIN_SCREEN_X											0
#define MAIN_SCREEN_Y											0
#define MAIN_SCREEN_WIDTH										320
#define MAIN_SCREEN_HEIGHT										240
#define MAIN_SCREEN_BACKGROUND_COLOR							GRAPHICS_SET_COLOR(0, 0, 0)
#define MAIN_SCREEN_OUTLINE										0

//----------------------------------------------------------------------------------------------------------//

#define MAIN_SCREEN_STATUS_BAR_LAYOUT_X							MAIN_SCREEN_X
#define MAIN_SCREEN_STATUS_BAR_LAYOUT_Y							MAIN_SCREEN_Y
#define MAIN_SCREEN_STATUS_BAR_LAYOUT_WIDTH						MAIN_SCREEN_WIDTH
#define MAIN_SCREEN_STATUS_BAR_LAYOUT_HEIGHT					18

//----------------------------------------------------------------------------------------------------------//

#define MAIN_SCREEN_WAVEFORM_LAYOUT_X							MAIN_SCREEN_X
#define MAIN_SCREEN_WAVEFORM_LAYOUT_Y							LAYOUT_CACULATOR_POS_Y(MAIN_SCREEN_STATUS_BAR_LAYOUT_HEIGHT, MAIN_SCREEN_STATUS_BAR_LAYOUT_Y)
#define MAIN_SCREEN_WAVEFORM_LAYOUT_WIDTH						MAIN_SCREEN_WIDTH
#define MAIN_SCREEN_WAVEFORM_LAYOUT_HEIGHT						204

//----------------------------------------------------------------------------------------------------------//

#define MAIN_SCREEN_MEASUREMENT_BAR_LAYOUT_X					MAIN_SCREEN_X
#define MAIN_SCREEN_MEASUREMENT_BAR_LAYOUT_Y					LAYOUT_CACULATOR_POS_Y(MAIN_SCREEN_WAVEFORM_LAYOUT_HEIGHT, MAIN_SCREEN_WAVEFORM_LAYOUT_Y)
#define MAIN_SCREEN_MEASUREMENT_BAR_LAYOUT_WIDTH				MAIN_SCREEN_WIDTH
#define MAIN_SCREEN_MEASUREMENT_BAR_LAYOUT_HEIGHT				18

//----------------------------------------------------------------------------------------------------------//
#endif /* UI_MAINSCREEN_INC_MAINSCREENLAYOUT_H_ */
