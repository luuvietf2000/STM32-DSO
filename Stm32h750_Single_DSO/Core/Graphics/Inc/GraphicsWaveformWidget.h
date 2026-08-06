#ifndef GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_
#define GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_

#include "Graphics.h"
#include "GraphicsRectangleWidget.h"

//-------------------------------------------------------------------------------------------------------------------//
typedef struct{
	GraphicsRectangleConfig *lines;
	uint16_t count;
} GraphicsLineSet;

typedef struct{
	GraphicsRectangleWidgetConfig background;
	GraphicsLineSet lineSet;
	GraphicsLineSet waveformPoints;
} GraphicsWaveformWidgetConfig;


//-------------------------------------------------------------------------------------------------------------------//
HAL_StatusTypeDef GraphicsWaveformAllocateWaveformPoint(GraphicsWaveformWidgetConfig *waveform, uint16_t length);
HAL_StatusTypeDef GraphicsWaveformAllocateLineSet(GraphicsWaveformWidgetConfig *waveform, uint16_t length);
HAL_StatusTypeDef GraphicsDrawWaveformWidgetLineSet(GraphicsWaveformWidgetConfig *waveform);
HAL_StatusTypeDef GraphicsDrawWaveformWidgetWavePoints(GraphicsWaveformWidgetConfig *waveform);
HAL_StatusTypeDef GraphicsWaveformUpdateLine(GraphicsWaveformWidgetConfig *waveform, uint16_t pos, GraphicsRectangleConfig *newPoint);
HAL_StatusTypeDef GraphicsDrawWaveformWidgetBackground(GraphicsWaveformWidgetConfig *waveform);
HAL_StatusTypeDef GraphicsRemoveLineOld(GraphicsWaveformWidgetConfig *waveform, uint16_t pos, GraphicsRectangleConfig *newPoint);
HAL_StatusTypeDef GraphicsDrawWaveformPointLine(GraphicsWaveformWidgetConfig *waveform, uint16_t pos);
HAL_StatusTypeDef GraphicsWaveformUpdateNewRange(GraphicsRectangleConfig *old, GraphicsRectangleConfig *new, St7789RgbColor *color);
//-------------------------------------------------------------------------------------------------------------------//

#endif /* GRAPHICS_INC_GRAPHICSWAVEFORMWIDGET_H_ */
