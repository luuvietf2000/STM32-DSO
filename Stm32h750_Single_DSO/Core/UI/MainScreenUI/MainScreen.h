#ifndef UI_MAINSCREEN_INC_MAINSCREEN_H_
#define UI_MAINSCREEN_INC_MAINSCREEN_H_

#include "MainScreenLayout.h"
#include "Graphics.h"
#include "StatusBar/StatusBar.h"
#include "MeasurementBar/MeasurementBar.h"
#include "Waveform/Waveform.h"

//----------------------------------------------------------------------------------------------------------//
typedef struct{
	uint32_t voltage;
	uint32_t time;
	AcquisittionState aquisittionState;
	TriggerModeState triggerMode;
	TriggerEdgeState triggerEdge;
	uint16_t zoomScale;
	uint32_t triggerLevel;
} StatusBarConfig;

typedef struct{
	uint32_t voltageMax;
	uint32_t voltageMin;
} MeasurementBarConfig;

//----------------------------------------------------------------------------------------------------------//
extern void WaveformPushPoint(uint32_t start, uint32_t end);
//-------------------------------------------------------------------//
void MainScrrenInit(StatusBarConfig *statusBarParameter, MeasurementBarConfig *measurementBarParameter);
void StatusBarRequestChanged(StatusBarConfig *statusBarParameter);
void MeasurementBarRequestChanged(MeasurementBarConfig *measurementBarParameter);
//----------------------------------------------------------------------------------------------------------//

#endif /* UI_MAINSCREEN_INC_MAINSCREEN_H_ */
