#include "GraphicsWaveformWidget.h"
#include "GraphicsRectangleWidget.h"
#include <stdlib.h>
//-----------------------------------------------------------------------------------------------------------//
#define GRAPHICS_WAVEFORM_WIDGET_IS_IN_RANGE(point, min, max)						(point >= min && point <= max)

//-----------------------------------------------------------------------------------------------------------//
static HAL_StatusTypeDef GraphicsWaveformAllocate(GraphicsLineSet *lines, uint16_t pointLenght);
static HAL_StatusTypeDef GraphicsWaveformChangedLine(GraphicsRectangleConfig *old, GraphicsRectangleConfig *new, St7789RgbColor *color);
static HAL_StatusTypeDef GraphicsDrawLines(GraphicsLineSet *lines);
//-----------------------------------------------------------------------------------------------------------//
static HAL_StatusTypeDef GraphicsWaveformAllocate(GraphicsLineSet *lines, uint16_t length){
	lines->count = length;
	lines->lines = malloc(length * sizeof(GraphicsRectangleConfig));
	if(lines->lines == NULL)
		return HAL_ERROR;
	return HAL_OK;
}

HAL_StatusTypeDef GraphicsWaveformAllocateLineSet(GraphicsWaveformWidgetConfig *waveform, uint16_t length){
	return GraphicsWaveformAllocate(&waveform->lineSet, length);
}

HAL_StatusTypeDef GraphicsWaveformAllocateWaveformPoint(GraphicsWaveformWidgetConfig *waveform, uint16_t length){
	return GraphicsWaveformAllocate(&waveform->waveformPoints, length);
}

HAL_StatusTypeDef GraphicsDrawWaveformWidgetBackground(GraphicsWaveformWidgetConfig *waveform){
	return GraphicsDrawRectangleWidget(&waveform->background);
}

HAL_StatusTypeDef GraphicsDrawWaveformWidgetLineSet(GraphicsWaveformWidgetConfig *waveform){
	HAL_StatusTypeDef result = HAL_OK;
	if(waveform->lineSet.lines != NULL){
		for(uint16_t i = 0; i < waveform->lineSet.count; i++){
			result |= GraphicsDrawRectangle(waveform->lineSet.lines + i);
		}
	}
	return result;
}

HAL_StatusTypeDef GraphicsDrawWaveformWidgetWavePoints(GraphicsWaveformWidgetConfig *waveform){
	HAL_StatusTypeDef result = HAL_OK;
	if(waveform->waveformPoints.lines != NULL){
		for(uint16_t i = 0; i < waveform->waveformPoints.count; i++){
			result |= GraphicsDrawRectangle(waveform->waveformPoints.lines + i);
		}
	}
	return HAL_ERROR;
}

static HAL_StatusTypeDef GraphicsDrawLines(GraphicsLineSet *lines){
	HAL_StatusTypeDef result = HAL_OK;
	for(uint16_t i = 0; i < lines->count; i++){
		result |= GraphicsDrawRectangle(lines->lines + i);
	}
	return result;
}

HAL_StatusTypeDef GraphicsDrawWaveformPointLine(GraphicsWaveformWidgetConfig *waveform, uint16_t pos){
	return GraphicsDrawRectangle(waveform->waveformPoints.lines + pos);
}

HAL_StatusTypeDef GraphicsRemoveLineOld(GraphicsWaveformWidgetConfig *waveform, uint16_t pos, GraphicsRectangleConfig *newPoint){
	if(pos >= waveform->waveformPoints.count)
		return HAL_ERROR;
	return GraphicsWaveformChangedLine(
		&waveform->waveformPoints.lines[pos],
		newPoint,
		&waveform->background.rectangle.background
	);
}

static HAL_StatusTypeDef GraphicsWaveformChangedLine(GraphicsRectangleConfig *old, GraphicsRectangleConfig *new, St7789RgbColor *color){
	HAL_StatusTypeDef result = HAL_OK;
	GraphicsRectangleConfig areaNeedChanged;
	areaNeedChanged.background = *(color);
	uint16_t yStartOld = old->pos.coordinate.y;
	uint16_t yEndOld = yStartOld + old->pos.size.row;
	uint16_t yStartNew = new->pos.coordinate.y;
	uint16_t yEndNew = yStartNew + new->pos.size.row;
	float us;
	if(yStartNew > yStartOld){
		areaNeedChanged.pos.coordinate = old->pos.coordinate;
		areaNeedChanged.pos.size = (St7789Size) {
			old->pos.size.column,
			yStartNew - yStartOld
		};
		result |= GraphicsDrawRectangle(&areaNeedChanged);
	}

	if(yEndOld > yEndNew){
		areaNeedChanged.pos.coordinate = (St7789Coordinate) {
			old->pos.coordinate.x,
			yEndNew
		};
		areaNeedChanged.pos.size = (St7789Size) {
			old->pos.size.column,
			yEndOld - yEndNew
		};
		result |= GraphicsDrawRectangle(&areaNeedChanged);
	}
	if(yEndOld <= yStartNew || yEndNew <= yStartOld){
		areaNeedChanged.pos = old->pos;
		result |= GraphicsDrawRectangle(&areaNeedChanged);
	}
	return result;
}
HAL_StatusTypeDef GraphicsWaveformUpdateNewRange(GraphicsRectangleConfig *old, GraphicsRectangleConfig *new, St7789RgbColor *color){
	return GraphicsWaveformChangedLine(old, new, color);
}

HAL_StatusTypeDef GraphicsWaveformUpdateLine(GraphicsWaveformWidgetConfig *waveform, uint16_t pos, GraphicsRectangleConfig *newPoint){
	if(pos >= waveform->waveformPoints.count)
		return HAL_ERROR;
	HAL_StatusTypeDef result = HAL_OK;
	waveform->waveformPoints.lines[pos] = *newPoint;
	return result;
}
