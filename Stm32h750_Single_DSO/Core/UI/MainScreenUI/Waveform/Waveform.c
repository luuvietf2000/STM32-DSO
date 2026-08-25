#include "Waveform.h"
#include "GraphicsWaveformWidget.h"

//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//

void WaveformInit(){
	GraphicsDrawWaveformWidget((GraphicsWaveformWidget*) &waveformWidget);
}
void WaveformPushPoint(uint32_t start, uint32_t end){
	GraphicsWaveformPushPoint((GraphicsWaveformWidget*) &waveformWidget, start, end);
}

void WaveforomUpdate(GraphicsPoint *point, uint32_t size){
	GraphicsWaveformUpdate((GraphicsWaveformWidget*) &waveformWidget, point, size);
}

