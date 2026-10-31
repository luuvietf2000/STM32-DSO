#ifndef UI_MAINSCREENUI_WAVEFORM_WAVEFORM_H_
#define UI_MAINSCREENUI_WAVEFORM_WAVEFORM_H_

#include "GraphicsWaveformWidget.h"

//----------------------------------------------------------------------------------------------------------//
extern const GraphicsWaveformWidget waveformWidget;
//----------------------------------------------------------------------------------------------------------//
void WaveformInit();
void WaveformUpdate(GraphicsPoint *point, uint32_t size);
void WaveformPushPoint(GraphicsPoint *point, uint32_t size);
#endif /* UI_MAINSCREENUI_WAVEFORM_WAVEFORM_H_ */
