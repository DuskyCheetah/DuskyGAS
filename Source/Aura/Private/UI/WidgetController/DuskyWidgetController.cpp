// Copyright DuskyDev!


#include "UI/WidgetController/DuskyWidgetController.h"

void UDuskyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	// Init 4 key member variables to custom-struct values.
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
