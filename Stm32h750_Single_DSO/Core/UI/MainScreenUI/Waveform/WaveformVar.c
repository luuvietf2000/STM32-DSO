#include "WaveformVar.h"
#include "GraphicsWaveformWidget.h"

//----------------------------------------------------------------------------------------------------//
static GraphicsPoint points[WAVEFORM_CONTENT_WIDTH];

static GraphicsWaveformPoints pointLines = {
	.points = points,
	.pointCount = 0,
	.pointColor = WAVEFORM_POINT_BACKGROUND
};

const GraphicsWaveformWidget waveformWidget = {
	.x = WAVEFORM_X,
	.y = WAVEFORM_Y,
	.width = WAVEFORM_WIDTH,
	.height = WAVEFORM_HEIGH,
	.background = WAVEFORM_BACKGROUND,
	.borderWidth = WAVEFORM_OUTLINE_WIDTH,
	.borderColor = WAVEFORM_OUTLINE_COLOR,
	.divisionXLine = WAVEFORM_DIVISION_PIXEL,
	.divisionYLine = WAVEFORM_DIVISION_PIXEL,
	.divisionLineColor = WAVEFORM_LINE_SET_BACKGROUND,
	.pointLines = &pointLines
};
//----------------------------------------------------------------------------------------------------//
