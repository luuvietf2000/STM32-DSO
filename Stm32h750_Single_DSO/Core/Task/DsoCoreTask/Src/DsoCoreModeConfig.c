#include "DsoCoreModeConfig.h"


//----------------------------------------------------------------------------------------------------------//
#define DSO_CORE_MODE_VOLTAGE_DEFAULT                  1
#define DSO_CORE_MODE_TIME_DEFAULT                     1
#define DSO_CORE_MODE_ACQUISITTION_STATE_DEFAULT      ACQUISITTION_RUN_STATE
#define DSO_CORE_MODE_ZOOM_SCALE_DEFAULT              100
#define DSO_CORE_MODE_TRIGGER_MODE_DEFAULT            TRIGGER_AUTO
#define DSO_CORE_MODE_TRIGGER_EDGE_DEFAULT            TRIGGER_RISSING_EDGE
#define DSO_CORE_MODE_TRIGGER_LEVEL_DEFAULT           1

#define DSO_CORE_MODE_VOLTAGE_MAX_DEFAULT             0
#define DSO_CORE_MODE_VOLTAGE_MIN_DEFAULT             0
//----------------------------------------------------------------------------------------------------------//
StatusBarConfig statusBarConfig = {
    .voltage = DSO_CORE_MODE_VOLTAGE_DEFAULT,
    .time = DSO_CORE_MODE_TIME_DEFAULT,
    .aquisittionState = DSO_CORE_MODE_ACQUISITTION_STATE_DEFAULT,
    .zoomScale = DSO_CORE_MODE_ZOOM_SCALE_DEFAULT,
    .triggerMode = DSO_CORE_MODE_TRIGGER_MODE_DEFAULT,
    .triggerEdge = DSO_CORE_MODE_TRIGGER_EDGE_DEFAULT,
    .triggerLevel = DSO_CORE_MODE_TRIGGER_LEVEL_DEFAULT
};

MeasurementBarConfig measurementBarConfig = {
    .voltageMax = DSO_CORE_MODE_VOLTAGE_MAX_DEFAULT,
    .voltageMin = DSO_CORE_MODE_VOLTAGE_MIN_DEFAULT
};
//----------------------------------------------------------------------------------------------------------//
