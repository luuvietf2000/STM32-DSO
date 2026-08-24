#include "GraphicsWaveformWidget.h"
#include "GraphicsRectangleWidget.h"
#include "Graphics.h"
//----------------------------------------------------------------------------------------------------------//
static void GraphicsWaveformUpdatePoint(GraphicsWaveformWidget *waveform, GraphicsPoint *new, GraphicsPoint *old, uint32_t contentX, uint32_t contentY, uint32_t x);
static void GraphicWaveformDrawBackground(GraphicsWaveformWidget *waveform);
static void GraphicsWaveformCaculatorContentSize(GraphicsWaveformWidget *waveform, uint32_t *contentX, uint32_t *contentWidth, uint32_t *contentY, uint32_t *contentHeight);
static void GraphicsWaveformDrawDivisionYLine(GraphicsWaveformWidget *waveform, uint32_t contentX, uint32_t contentWidth, uint32_t contentY, uint32_t contentHeight);
static void GraphicsWaveformDrawDivisionXLine(GraphicsWaveformWidget *waveform, uint32_t contentX, uint32_t contentWidth, uint32_t contentY, uint32_t contentHeight);
//----------------------------------------------------------------------------------------------------------//

void GraphicsDrawWaveformWidget(GraphicsWaveformWidget *waveform){
	GraphicWaveformDrawBackground(waveform);
	uint32_t contentX, contentY, contentWidth, contentHeight;
	GraphicsWaveformCaculatorContentSize(waveform, &contentX, &contentWidth, &contentY, &contentHeight);
	if(waveform->divisionXLine != 0){
		GraphicsWaveformDrawDivisionXLine(waveform, contentX, contentWidth, contentY, contentHeight);
	}

	if(waveform->divisionYLine != 0){
		GraphicsWaveformDrawDivisionYLine(waveform, contentX, contentWidth, contentY, contentHeight);
	}

	waveform->pointLines->pointDisplay = 0;
}

static void GraphicsWaveformCaculatorContentSize(GraphicsWaveformWidget *waveform, uint32_t *contentX, uint32_t *contentWidth, uint32_t *contentY, uint32_t *contentHeight){
	*contentX = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->x, waveform->borderWidth);
	*contentY = GRAPHICS_WAVEFORM_CONTENT_POS(waveform->y, waveform->borderWidth);
	*contentWidth = GRAPHICS_WAVEFORM_CONTENT_SIZE(waveform->width, waveform->borderWidth);
	*contentHeight = GRAPHICS_WAVEFORM_CONTENT_SIZE(waveform->height, waveform->borderWidth);
}

static void GraphicsWaveformDrawDivisionYLine(GraphicsWaveformWidget *waveform, uint32_t contentX, uint32_t contentWidth, uint32_t contentY, uint32_t contentHeight){
	GraphicsRectangleWidget rec;
	uint32_t row, lines;
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
static void GraphicsWaveformDrawDivisionXLine(GraphicsWaveformWidget *waveform, uint32_t contentX, uint32_t contentWidth, uint32_t contentY, uint32_t contentHeight){
	GraphicsRectangleWidget rec;
	uint32_t column, lines;
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

static void GraphicWaveformDrawBackground(GraphicsWaveformWidget *waveform){
	GraphicsRectangleWidget rec;
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
	} else{

	}
}

static void GraphicsWaveformUpdatePoint(GraphicsWaveformWidget *waveform, GraphicsPoint *new, GraphicsPoint *old, uint32_t contentX, uint32_t contentY, uint32_t x){
	uint32_t yStart = GRAPHICS_GET_MIN(new->start, old->start);
	uint32_t yEnd = GRAPHICS_GET_MAX(new->end, new->end);
	uint32_t prefecrredSize = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(GRAPHICS_WAVEFORM_POINT_LINE_SIZE, yEnd - yStart));
	uint8_t *data = NULL;
	GraphicsGetPointerMemory(&data, prefecrredSize, prefecrredSize);
	uint32_t flag = x % waveform->divisionXLine == 0;
	if(flag){
		uint32_t color = flag == 0 ? waveform->divisionLineColor : waveform->background;
		GraphicsDma2dSetOffsetPixel(0);
		GraphicsDma2dFillModeStart(prefecrredSize / GRAPHICS_PIXEL_PER_BYTE, 1, data, color);
	}
	if(flag != 0){
		uint32_t lines = (yEnd - yStart) % waveform->divisionYLine;
		GraphicsDma2dSetOffsetPixel(waveform->divisionYLine);
		GraphicsDma2dFillModeStart(lines, 1, data + GRAPHICS_GET_PIXEL_BYTE(x % waveform->divisionYLine), waveform->divisionLineColor);
	}
	GraphicsDma2dSetOffsetPixel(0);
	uint32_t pixelNewSize = new->end - new->start;
	GraphicsDma2dFillModeStart(pixelNewSize, 1, data, waveform->pointLines->pointColor);
	GraphicsTransfer(data, prefecrredSize, GRAPHICS_WAVEFORM_POINT_LINE_SIZE);
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
