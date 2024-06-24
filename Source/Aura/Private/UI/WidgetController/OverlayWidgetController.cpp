// Copyright DuskyDev!


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// Obtain pointer to DuskyAttributeSet
	const UDuskyAttributeSet* DuskyAttributeSet = CastChecked<UDuskyAttributeSet>(AttributeSet);

	// Use GETTERS from the set to obtain the current value of these attributes
	OnHealthChanged.Broadcast(DuskyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DuskyAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DuskyAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DuskyAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Obtain pointer to DuskyAttributeSet
	const UDuskyAttributeSet* DuskyAttributeSet = CastChecked<UDuskyAttributeSet>(AttributeSet);

	// Anytime Health changes - HealthChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	// Anytime MaxHealth changes - MaxHealthChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	// Anytime Mana changes - ManaChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	// Anytime MaxMana changes - MaxManaChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	Cast<UDuskyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[](const FGameplayTagContainer& AssetTags /*InputParameter*/)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// TODO: Broadcast the tag to the Widget Controller
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);
			}
		}
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
