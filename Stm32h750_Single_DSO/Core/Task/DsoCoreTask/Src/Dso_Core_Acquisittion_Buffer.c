#include "Dso_Core_Acquisittion_Buffer.h"

//-------------------------------------------------------------------------------------------------------------------------//
#define DSO_CORE_ACQUISITITON_BUFFER_NEXT_INDEX(x, size)								((x + size) >= DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH ? 0 : (x + size))
#define DSO_CORE_ACQUISITTION_BUFFER_PER_INDEX(x, size)									((x < size) ? (DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH - (size - x)) : (x - size))
#define DSO_CORE_ACQUISITTION_BUFFER_LEVEL												(DSO_CORE_ACQUISITTION_SAMPLE_LEVELS - 1)
#define DSO_CORE_ACQUISITTION_Y_PIXEL_MAX												(DSO_CORE_ACQUISITTION_Y_PIXELS_DISPLAY - 1)
#define DSO_CORE_ACQUISITTION_Y_START_OFFSET											0
#define DSO_CORE_ACQUISITTION_Y_END_OFFSET												1
#define DSO_CORE_ACQUISITTION_CONVERT_LEVEL(level)										((float) level * DSO_CORE_ACQUISITTION_SAMPLE_VOLTAGE_MAX / DSO_CORE_ACQUISITTION_BUFFER_LEVEL)
//--------------------------------------------------------//
#if(DSO_CORE_ACQUISITTION_INVERT_MODE == DSO_CORE_ACQUISITTION_INVERT_PIXEL)
	#define DSO_CORE_ACQUISITION_BUFFER_GET_PIXEL(level, range)							(DSO_CORE_ACQUISITTION_Y_PIXEL_MAX - ((uint32_t) level * DSO_CORE_ACQUISITTION_Y_PIXEL_MAX) / range)
#else
	#define DSO_CORE_ACQUISITION_BUFFER_GET_PIXEL(level, range)							(((uint32_t) level * DSO_CORE_ACQUISITTION_Y_PIXEL_MAX) / range)
#endif
//-------------------------------------------------------------------------------------------------------------------------//
__attribute__((section(".dma_buffer")))
static uint16_t acquisittionBuffer[DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH];
static uint16_t writeIndex;
static uint16_t readIndex;
static DsoCoreAcquisittionBufferState memoryState;
static GraphicsPoint *point = NULL;
static uint32_t detectedSampleCount;
static uint32_t detectedSampleIndex;
static uint32_t maxSample;
static uint32_t minSample;
static uint32_t samplePerPixel = 100;
static uint32_t levelMax;
static uint32_t levelMin;
static uint32_t levelMaxChuck;
static uint32_t levelMinChuck;
//-------------------------------------------------------------------------------------------------------------------------//
static void DsoCoreGetPointPixel(uint32_t *pixel, uint32_t level, uint32_t offset, uint32_t levelMax, uint32_t levelMin);
static void DsoCoreGetPeakDetectedSamples(GraphicsPoint *ptr, uint32_t indexBufferStart, uint32_t *sampleIndex, uint32_t *maxSample, uint32_t *minSample, uint32_t *maxChuck, uint32_t *minChuck,  uint32_t levelMax, uint32_t levelMin, uint32_t scaleSample);
//-------------------------------------------------------------------------------------------------------------------------//
uint16_t *DsoCoreGetAcquisitionBufferNextWritePtr(uint32_t size){
	memoryState = DSO_CORE_TASK_ACQUISITTION_BUFFER_MEMORY_AVAILABLE;
	return acquisittionBuffer + DSO_CORE_ACQUISITITON_BUFFER_NEXT_INDEX(writeIndex, size);
}

uint16_t *DsoCoreGetAcquisitionBufferPerWritePtr(uint32_t size){
	return acquisittionBuffer + DSO_CORE_ACQUISITTION_BUFFER_PER_INDEX(readIndex, size);
}

static void DsoCoreGetPointPixel(uint32_t *pixel, uint32_t level, uint32_t offset, uint32_t levelMax, uint32_t levelMin){
	if(level > levelMax){
		level = levelMax - levelMin;
	} else if(level < levelMin){
		level = 0;
	} else
		level -= levelMin;
	*pixel = DSO_CORE_ACQUISITION_BUFFER_GET_PIXEL(level, levelMax - levelMin) + offset;
}

static void DsoCoreGetPeakDetectedSamples(GraphicsPoint *ptr, uint32_t indexBufferStart, uint32_t *sampleIndex, uint32_t *maxSample, uint32_t *minSample, uint32_t *maxChuck, uint32_t *minChuck,  uint32_t levelMax, uint32_t levelMin, uint32_t scaleSample){
	uint32_t remaining;
	uint32_t indexPoint = *sampleIndex / scaleSample;
	uint32_t index = indexBufferStart;
	const uint32_t latchIndex = scaleSample - 1;
	const uint32_t size = scaleSample * DSO_CORE_ACQUISITTION_X_PIXELS_DISPLAY;
	for(uint32_t i = 0; i < size; i++){
		remaining = *sampleIndex % scaleSample;
		if(remaining == 0){
			indexPoint = *sampleIndex / scaleSample;
			*maxSample = *minSample = acquisittionBuffer[index];
		}
		if(*maxSample < acquisittionBuffer[index]){
			*maxSample = acquisittionBuffer[index];
		} else if(*minSample > acquisittionBuffer[index]){
			*minSample = acquisittionBuffer[index];
		}
		if(remaining == latchIndex){
			DsoCoreGetPointPixel(&ptr[indexPoint].start, *maxSample, DSO_CORE_ACQUISITTION_Y_START_OFFSET, levelMax, levelMin);
			DsoCoreGetPointPixel(&ptr[indexPoint].end, *minSample, DSO_CORE_ACQUISITTION_Y_END_OFFSET, levelMax, levelMin);
			if(*maxChuck < *maxSample)
				*maxChuck = *maxSample;
			if(*minChuck > *minSample)
				*minChuck = *minSample;
		}
		index++;
		(*sampleIndex)++;
		if(index == DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH)
			index = 0;
	}
}

static uint32_t DsoCoreGetAcquisittionBufferSize(){
	uint32_t size = 0;
	if(memoryState != DSO_CORE_TASK_ACQUISITTION_BUFFER_MEMORY_EMPTY){
		if(readIndex < writeIndex)
			size += (writeIndex - readIndex);
		else
			size += (DSO_CORE_TASK_SAMPLE_BUFFER_LENGTH - readIndex) + writeIndex;
	}
	return size;
}

void DsoCoreProcessAcquisitionBufferChunk(GraphicsPoint *ptr, float *voltageMax, float *voltageMin){
	uint32_t size = DsoCoreGetAcquisittionBufferSize();
	uint32_t samplesRequired = samplePerPixel * DSO_CORE_ACQUISITTION_X_PIXELS_DISPLAY;
	if(size < samplesRequired)
		return;
	levelMaxChuck = levelMinChuck = acquisittionBuffer[readIndex];
	DsoCoreGetPeakDetectedSamples(
		ptr,
		readIndex,
		&detectedSampleIndex,
		&levelMaxChuck,
		&levelMinChuck,
		&maxSample,
		&minSample,
		levelMax,
		levelMin,
		samplePerPixel
	);
	*voltageMax = DSO_CORE_ACQUISITTION_CONVERT_LEVEL(levelMaxChuck);
	*voltageMin = DSO_CORE_ACQUISITTION_CONVERT_LEVEL(levelMinChuck);
	readIndex += samplesRequired;
}
