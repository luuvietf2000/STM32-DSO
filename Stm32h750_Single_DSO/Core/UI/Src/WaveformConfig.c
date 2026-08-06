#include "WaveformConfig.h"

//----------------------------------------------------------------------------------------------------//
static GraphicsRectangleConfig waveformPoint[WAVEFORM_POINT_LENGTH];
static GraphicsRectangleConfig rec[WAVEFORM_POINT_LENGTH];
//----------------------------------------------------------------------------------------------------//

void WaveformWidgetInit(){
	waveform.waveformPoints.lines = waveformPoint;
	waveform.waveformPoints.count = WAVEFORM_POINT_LENGTH;
	for(uint16_t i = 0; i < WAVEFORM_POINT_LENGTH; i++){
		waveformPoint[i].background = (St7789RgbColor) WAVEFORM_POINT_BACKGROUND;
		waveformPoint[i].pos.coordinate = (St7789Coordinate) {WAVEFORM_HORIZONTAL_LINE_X + i, 100};
		waveformPoint[i].pos.size = (St7789Size) {1, 50};
	}
	uint32_t start, time;

	start = HAL_GetTick();
	GraphicsDrawWaveformWidgetBackground(&waveform);


	GraphicsDrawWaveformWidgetLineSet(&waveform);


	GraphicsDrawWaveformWidgetWavePoints(&waveform);
	time = HAL_GetTick() - start;

	for(uint16_t i = 0; i < WAVEFORM_POINT_LENGTH; i++){
		rec[i].background = (St7789RgbColor) WAVEFORM_POINT_BACKGROUND;
		rec[i].pos.size = (St7789Size) {1, 15};
		rec[i].pos.coordinate = (St7789Coordinate) {WAVEFORM_HORIZONTAL_LINE_X + i, 120};
	}


	for(uint16_t i = 0; i < WAVEFORM_POINT_LENGTH; i++){
		GraphicsRemoveLineOld(&waveform, i, rec + i);
	}

	GraphicsDrawWaveformWidgetLineSet(&waveform);



	for(uint16_t i = 0; i < WAVEFORM_POINT_LENGTH; i++){
		GraphicsWaveformUpdateLine(&waveform, i, rec + i);
		GraphicsDrawWaveformPointLine(&waveform, i);
		/*
		if(i % WAVEFORM_DIVISION_PIXEL != 0){
			GraphicsWaveformUpdateNewRange(rec + i, waveform.waveformPoints.lines + i, &waveform.waveformPoints.lines->background);
			GraphicsDrawWaveformPointLine(&waveform, i);
		}
		else{

		}
		*/
	}

}

HAL_StatusTypeDef WaveformDrawWidgetLineSet(){
	return HAL_OK;
}

HAL_StatusTypeDef WaveformDrawWidgetPushLine(uint16_t max, uint16_t min){
	HAL_StatusTypeDef result = HAL_OK;

	return result;
}
