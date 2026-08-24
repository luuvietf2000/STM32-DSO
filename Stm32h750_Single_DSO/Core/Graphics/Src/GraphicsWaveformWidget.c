#include "GraphicsWaveformWidget.h"
#include "GraphicsRectangleWidget.h"
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
void GraphicsDrawWaveformWidget(GraphicsWaveformWidget *waveform){
	GraphicsRectangleWidget rec;
	// Draw background

	GraphicsRectangleSetParameter(
		&rec,
		waveform->x,
		waveform->y,
		waveform->width,
		waveform->height,
		waveform->background,
		waveform->borderColor,
		waveform->borderWidth
	);
	GraphicsDrawRectangleWidget(&rec);
	uint32_t contentX = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->x, waveform->borderWidth);
	uint32_t contentY = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->y, waveform->borderWidth);
	uint32_t contentWidth = GRAPHICS_WAVEFORM_CONTENT_SIZE(waveform->width, waveform->borderWidth);
	uint32_t contentHeight = GRAPHICS_WAVEFORM_CONTENT_SIZE(waveform->height, waveform->borderWidth);
	uint16_t lines;


	if(waveform->divisionXLine != 0){
		uint32_t column;
		// Draw Division X Lines
		lines = contentWidth / waveform->divisionXLine;
		lines -= (contentWidth % waveform->divisionXLine ? 0 : 1);
		for(uint32_t line = 0; line < lines; line++){
			column = contentX + waveform->divisionXLine * (line + 1);
			GraphicsRectangleSetParameter(
				&rec,
				column,
				contentY,
				GRAPHICS_WAVEFORM_DIVISION_SIZE,
				contentHeight,
				waveform->divisionLineColor,
				0,
				0
			);
			GraphicsDrawRectangleWidget(&rec);
		}
	}

	if(waveform->divisionYLine != 0){
		uint32_t row;
		// Draw Division Y Lines
		lines = contentHeight / waveform->divisionYLine;
		lines -= (contentHeight % waveform->divisionYLine ? 0 : 1);
		for(uint32_t line = 0; line < lines; line++){
			row = contentY + waveform->divisionYLine * (line + 1);
			GraphicsRectangleSetParameter(
				&rec,
				contentX,
				row,
				contentWidth,
				GRAPHICS_WAVEFORM_DIVISION_SIZE,
				waveform->divisionLineColor,
				0,
				0
			);
			GraphicsDrawRectangleWidget(&rec);
		}
	}

	waveform->pointLines->pointDisplay = 0;
}

void GraphicsWaveformPushPoint(GraphicsWaveformWidget *waveform, uint32_t start, uint32_t end){
	uint32_t contentHeight = GRAPHICS_WAVEFORM_CONTENT_SIZE(waveform->height, waveform->borderWidth);
	if(end < start || (end - start) > contentHeight)
		return;
	uint32_t contentX = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->x, waveform->borderWidth);
	uint32_t contentY = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->y, waveform->borderWidth);

	if(waveform->pointLines->pointDisplay < waveform->pointLines->pointCount){
		GraphicsRectangleWidget rec;
		GraphicsRectangleSetParameter(
			&rec,
			contentX + waveform->pointLines->pointDisplay,
			contentY + start,
			GRAPHICS_WAVEFORM_POINT_LINE_SIZE,
			end - start,
			waveform->pointLines->pointColor,
			0,
			0
		);
		GraphicsDrawRectangleWidget(&rec);
		waveform->pointLines->pointDisplay++;
	}

}

void GraphicsWaveformSetParameter(
    GraphicsWaveformWidget *waveform,
    uint32_t x,
    uint32_t y,
    uint32_t width,
    uint32_t height,
    uint32_t background,
    uint32_t divisionXLine,
    uint32_t divisionYLine,
    uint32_t divisionLineColor,
    uint32_t borderWidth,
    uint32_t borderColor)
{
    waveform->x = x;
    waveform->y = y;
    waveform->width = width;
    waveform->height = height;
    waveform->background = background;
    waveform->divisionXLine = divisionXLine;
    waveform->divisionYLine = divisionYLine;
    waveform->divisionLineColor = divisionLineColor;
    waveform->borderWidth = borderWidth;
    waveform->borderColor = borderColor;
}
