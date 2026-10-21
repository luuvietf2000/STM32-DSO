#ifndef UI_MAINSCREENUI_STATUSBAR_STATUSBAR_H_
#define UI_MAINSCREENUI_STATUSBAR_STATUSBAR_H_

#include "StatusBarConfig.h"
#include "StatusBarLayout.h"
#include "StatusBarVar.h"

//-----------------------------------------------------------------------------------------------------------------//
typedef enum{
	TRIGGER_AUTO,
	TRIIGGER_NORMAL,
	TRIGGER_SINGLE
} TriggerModeState;

typedef enum{
	TRIGGER_RISSING_EDGE,
	TRIGGER_FALLING_EDGE
} TriggerEdgeState;

typedef enum{
	ACQUISITTION_RUN_STATE,
	ACQUISITTION_STOP_STATE
} AcquisittionState;
//-----------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------//
extern const GraphicsTextWidget voltagePerDivisionText;
extern const GraphicsTextWidget timePerDivisionText;
extern const GraphicsTextWidget acquisittionStatusText;
extern const GraphicsTextWidget zoomScaleText;
extern const GraphicsTextWidget triggerModeText;
extern const GraphicsTextWidget triggerEdgeText;
extern const GraphicsTextWidget triggerLevelText;
//-----------------------------------------------------------------------------------------------------------------//

void SetTimePerDivWidget(uint32_t value);
void SetVoltagePerDivWidget(uint32_t value);
void SetZoomModeTextWidget(uint16_t scale);
void SetTriggerModeWidget(TriggerModeState state);
void SetAcquisittionStatusWidget(AcquisittionState state);
void SetTriggerEdgeWidget(TriggerEdgeState state);
void SetTriggerLevelWidget(uint32_t level);

#endif /* UI_MAINSCREENUI_STATUSBAR_STATUSBAR_H_ */
