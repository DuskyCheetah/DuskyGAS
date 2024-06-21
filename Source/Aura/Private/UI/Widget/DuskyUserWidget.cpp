// Copyright DuskyDev!


#include "UI/Widget/DuskyUserWidget.h"

void UDuskyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
