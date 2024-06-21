// Copyright DuskyDev!


#include "UI/HUD/DuskyHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/DuskyUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ADuskyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// Check if OverlayWidgetController exists
	if (OverlayWidgetController == nullptr)
	{
		// If not - create it
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// Set parameters with key variables
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	// Return either existing controller or newly created
	return OverlayWidgetController;
}

void ADuskyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Check if these classes exist - if not - provide detailed crash log descript
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_DuskyHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayC Widget Controller Class uninitialized, please fill out BP_DuskyHUD"));
	
	// Create Widget and Add to viewport.
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	// Cast to custom widget class to get our custom functions
	OverlayWidget = Cast<UDuskyUserWidget>(Widget);
	// Create Params struct with 4 key varaibles
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	// Initialize OverlayWidgetController
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	// Set the Widget Controller
	OverlayWidget->SetWidgetController(WidgetController);
	// Add Widget to Viewport
	Widget->AddToViewport();

	
}


