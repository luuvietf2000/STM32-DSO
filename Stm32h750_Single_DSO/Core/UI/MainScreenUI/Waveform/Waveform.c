#include "Waveform.h"
#include "GraphicsWaveformWidget.h"

//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//

void WaveformInit(){
	GraphicsDrawWaveformWidget((GraphicsWaveformWidget*) &waveformWidget);
}
void WaveformPushPoint(GraphicsPoint *point, uint32_t size){
	GraphicsWaveformPushPoint((GraphicsWaveformWidget*) &waveformWidget, point, size);
}

void WaveformUpdate(GraphicsPoint *point, uint32_t size){
	GraphicsWaveformUpdate((GraphicsWaveformWidget*) &waveformWidget, point, size);
}

