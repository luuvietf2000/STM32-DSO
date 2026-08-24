#ifndef UI_MAINSCREENUI_WAVEFORM_WAVEFORMLAYOUT_H_
#define UI_MAINSCREENUI_WAVEFORM_WAVEFORMLAYOUT_H_

#include "LayoutMacro.h"
#include "MainScreenLayout.h"
#include "Graphics.h"

//----------------------------------------------------------------------------------------------------//
#define WAVEFORM_X									(MAIN_SCREEN_WAVEFORM_LAYOUT_WIDTH - WAVEFORM_WIDTH) / 2
#define WAVEFORM_Y									MAIN_SCREEN_WAVEFORM_LAYOUT_Y
#define WAVEFORM_WIDTH								304
#define WAVEFORM_HEIGH								204

#define WAVEFORM_OUTLINE_WIDTH						2
#define WAVEFORM_OUTLINE_COLOR						GRAPHICS_SET_COLOR(0x80, 0, 0)
#define WAVEFORM_CONTENT_WIDTH						(WAVEFORM_WIDTH - WAVEFORM_OUTLINE_WIDTH * 2)
#define WAVEFORM_CONTENT_HEIGHT						(WAVEFORM_HEIGH - WAVEFORM_OUTLINE_WIDTH * 2)

#define WAVEFORM_BACKGROUND							MAIN_SCREEN_BACKGROUND_COLOR
#define WAVEFORM_DIVISION_PIXEL						20
#define WAVEFORM_LINE_SET_BACKGROUND				GRAPHICS_SET_COLOR(0x20, 0x20, 0x20)

#define WAVEFORM_POINT_BACKGROUND					GRAPHICS_SET_COLOR(0x00, 0x00, 0xFF)
//----------------------------------------------------------------------------------------------------//

#endif /* UI_MAINSCREENUI_WAVEFORM_WAVEFORMLAYOUT_H_ */
