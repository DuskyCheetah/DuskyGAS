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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const  FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	// Anytime MaxHealth changes - MaxHealthChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const  FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	// Anytime Mana changes - ManaChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetManaAttribute()).AddLambda(
		[this](const  FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	// Anytime MaxMana changes - MaxManaChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const  FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UDuskyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags /*InputParameter*/)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					// Broadcast the row obtained above
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}
