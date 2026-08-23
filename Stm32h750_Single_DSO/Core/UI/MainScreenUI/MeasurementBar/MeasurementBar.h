#ifndef UI_MAINSCREENUI_MEASUREMENTBAR_MEASUREMENTBAR_H_
#define UI_MAINSCREENUI_MEASUREMENTBAR_MEASUREMENTBAR_H_

#include "MeasurementBarVar.h"
#include "GraphicsTextWidget.h"

//-----------------------------------------------------------------------------------------------------//
extern const GraphicsTextWidget voltageMinText;
extern const GraphicsTextWidget voltageMaxText;
//-----------------------------------------------------------------------------------------------------//

void SetVoltageMaxWidget(uint32_t value);
void SetVoltageMinWidget(uint32_t value);

#endif /* UI_MAINSCREENUI_MEASUREMENTBAR_MEASUREMENTBAR_H_ */
