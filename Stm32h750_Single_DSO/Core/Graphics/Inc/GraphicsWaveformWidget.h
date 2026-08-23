#ifndef GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_
#define GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_

#include "stdint.h"
#include "Graphics.h"
//----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_WAVEFORM_CONTENT_POS(pos, borderWidth)											(pos + borderWidth)
#define GRAPHICS_WAVEFORM_CONTENT_SIZE(parentSize, borderSize)									(parentSize - 2 * borderSize)
#define GRAPHICS_WAVEFORM_DIVISION_SIZE															1
//----------------------------------------------------------------------------------------------------------//
typedef struct{
	GraphicsPoint *points;
	uint32_t pointCount;
	uint32_t pointColor;
} GraphicsWaveformPoints;

typedef struct{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint32_t background;
	uint32_t divisionXLine;
	uint32_t divisionYLine;
	uint32_t divisionLineColor;
	uint32_t borderWidth;
	uint32_t borderColor;
	GraphicsWaveformPoints *pointLines;
} GraphicsWaveformWidget;
//----------------------------------------------------------------------------------------------------------//

void GraphicsWaveformSetParameter(GraphicsWaveformWidget *waveform, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t background, uint32_t divisionXLine, uint32_t divisionYLine, uint32_t divisionLineColor, uint32_t borderWidth, uint32_t borderColor);
void GraphicsDrawWaveformWidget(GraphicsWaveformWidget *waveform);
#endif /* GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_ */
