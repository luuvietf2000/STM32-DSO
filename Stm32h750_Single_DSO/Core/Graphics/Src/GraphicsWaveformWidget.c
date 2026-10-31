#include "GraphicsWaveformWidget.h"
#include "GraphicsRectangleWidget.h"
#include "Graphics.h"
//----------------------------------------------------------------------------------------------------------//
static void GraphicsWaveformAddPoint(GraphicsWaveformWidget *waveform, uint32_t x, uint32_t contentX, uint32_t contentY, uint32_t start, uint32_t end);
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

static void GraphicsWaveformAddPoint(GraphicsWaveformWidget *waveform, uint32_t x, uint32_t contentX, uint32_t contentY, uint32_t start, uint32_t end){
    GraphicsRectangleWidget rec;
    GraphicsRectangleSetParameter(
        &rec,
        contentX + x,
        contentY + start,
        GRAPHICS_WAVEFORM_POINT_LINE_SIZE,
        end - start,
        waveform->pointLines->pointColor,
        0,
        0
    );
    GraphicsDrawRectangleWidget(&rec);
    GraphicsPoint *point = waveform->pointLines->points + waveform->pointLines->pointDisplay;
    point->start = start;
    point->end = end;
}

void GraphicsWaveformUpdate(GraphicsWaveformWidget *waveform, GraphicsPoint *new, uint32_t size){
	uint32_t contentX, contentY, contentWidth, contentHeight;
	GraphicsWaveformCaculatorContentSize(waveform, &contentX, &contentWidth, &contentY, &contentHeight);
	GraphicsPoint *ptr = waveform->pointLines->points;
	size = GRAPHICS_GET_MIN(size, waveform->pointLines->pointCount);
	for(uint32_t i = 0; i < size; i++){
		if(i < waveform->pointLines->pointDisplay){
			GraphicsWaveformUpdatePoint(
				waveform,
				new + i,
				ptr + i,
				contentX,
				contentY,
				i
			);
		} else{
			GraphicsWaveformAddPoint(waveform, i, contentX, contentY, (new + i)->start, (new + i)->end);
		}
		*(ptr + i) = *(new + i);
	}
	waveform->pointLines->pointDisplay = size;
}

void GraphicsWaveformPushPoint(GraphicsWaveformWidget *waveform, GraphicsPoint *points, uint32_t size){
	uint32_t contentX, contentY, contentWidth, contentHeight;
	GraphicsWaveformCaculatorContentSize(waveform, &contentX, &contentWidth, &contentY, &contentHeight);
	if(size == 0 || size > waveform->pointLines->pointCount)
		return;

	if(waveform->pointLines->pointDisplay < waveform->pointLines->pointCount){
		for(uint32_t i = 0; (i < size) && (waveform->pointLines->pointDisplay < waveform->pointLines->pointCount); i++){
			GraphicsWaveformAddPoint(
				waveform,
				waveform->pointLines->pointDisplay,
				contentX,
				contentY,
				(points + i)->start,
				(points + i)->end
			);
			*(waveform->pointLines->points + waveform->pointLines->pointDisplay) = *(points + i);
			waveform->pointLines->pointDisplay++;
		}
	} else{
		GraphicsPoint *ptr;
		uint32_t index = (waveform->pointLines->pointCount - size);
		for(uint32_t i = 0; i < index; i++){
			ptr = waveform->pointLines->points + i;
			GraphicsWaveformUpdatePoint(
				waveform,
				ptr + size,
				ptr,
				contentX,
				contentY,
				i
			);
			*ptr = *(ptr + size);
		}

		for(uint32_t i = 0; i < size; i++){
			ptr = waveform->pointLines->points + index + i;
			GraphicsWaveformUpdatePoint(
				waveform,
				points + i,
				ptr,
				contentX,
				contentY,
				index + i
			);
			*ptr = *(points + i);
		}
	}
}

static void GraphicsWaveformUpdatePoint(GraphicsWaveformWidget *waveform, GraphicsPoint *new, GraphicsPoint *old, uint32_t contentX, uint32_t contentY, uint32_t x){
	uint32_t yStart = GRAPHICS_GET_MIN(new->start, old->start);
	uint32_t yEnd = GRAPHICS_GET_MAX(new->end, old->end);
	GraphicsSetAreaRequest(
		contentX + x,
		contentX + x + GRAPHICS_WAVEFORM_POINT_LINE_SIZE,
		contentY + yStart,
		contentY + yEnd
	);
	uint8_t *data = NULL;
	uint32_t prefecrredSize = GRAPHICS_GET_PIXEL_BYTE(GRAPHICS_GET_PIXEL(GRAPHICS_WAVEFORM_POINT_LINE_SIZE, yEnd - yStart));
	uint32_t pixelStart;
	GraphicsGetPointerMemory(&data, prefecrredSize, prefecrredSize);
	if(yStart != new->start || yEnd != new->end){
		uint32_t isDivisionX = x % waveform->divisionXLine;
		uint32_t color = (isDivisionX == 0 && x != 0 ) ? waveform->divisionLineColor : waveform->background;
		GraphicsDma2dFillModeStart(GRAPHICS_WAVEFORM_ONE_PIXEL, prefecrredSize / GRAPHICS_PIXEL_PER_BYTE, data, color);
		uint32_t first = ((yStart + waveform->divisionYLine - GRAPHICS_WAVEFORM_ONE_PIXEL) / waveform->divisionYLine) * waveform->divisionYLine;
		if((isDivisionX != 0 || x == 0) && first < yEnd){
			if(first == 0)
				first += waveform->divisionYLine;
			if(first < yEnd){
				uint32_t lines = (yEnd - GRAPHICS_WAVEFORM_ONE_PIXEL - first) / waveform->divisionYLine + 1;
				pixelStart = first - yStart;
				GraphicsDma2dSetOffsetPixel(waveform->divisionYLine - GRAPHICS_WAVEFORM_ONE_PIXEL);
				GraphicsDma2dFillModeStart(lines, GRAPHICS_WAVEFORM_ONE_PIXEL, data + GRAPHICS_GET_PIXEL_BYTE(pixelStart), waveform->divisionLineColor);
			}
		}
	}

	uint32_t pixelNewSize = new->end - new->start;
	pixelStart =  new->start - yStart;
	GraphicsDma2dFillModeStart(GRAPHICS_WAVEFORM_ONE_PIXEL, pixelNewSize, data + GRAPHICS_GET_PIXEL_BYTE(pixelStart), waveform->pointLines->pointColor);
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
