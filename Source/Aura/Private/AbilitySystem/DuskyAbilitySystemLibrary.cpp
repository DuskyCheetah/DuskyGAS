// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/DuskyWidgetController.h"
#include "Player/DuskyPlayerState.h"
#include "UI/HUD/DuskyHUD.h"

UOverlayWidgetController* UDuskyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	// Obtain PlayerController - Must use WorldContextObject
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// Obtain DuskyHUD - if PC != Null
		if (ADuskyHUD* DuskyHUD = Cast<ADuskyHUD>(PC->GetHUD()))
		{
			// Obtain PlayerState
			ADuskyPlayerState* PS = PC->GetPlayerState<ADuskyPlayerState>();
			// Obtain ASC
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			// Obtain AS
			UAttributeSet* AS = PS->GetAttributeSet();

			// Create FWidgetControllerParams Struct
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			return DuskyHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UDuskyAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	// Obtain PlayerController - Must use WorldContextObject
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// Obtain DuskyHUD - if PC != Null
		if (ADuskyHUD* DuskyHUD = Cast<ADuskyHUD>(PC->GetHUD()))
		{
			// Obtain PlayerState
			ADuskyPlayerState* PS = PC->GetPlayerState<ADuskyPlayerState>();
			// Obtain ASC
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			// Obtain AS
			UAttributeSet* AS = PS->GetAttributeSet();

			// Create FWidgetControllerParams Struct
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			return DuskyHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
