// Copyright DuskyDev!


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "AbilitySystem/Data/DuskyAttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	// Obtain AS
	UDuskyAttributeSet* AS = CastChecked<UDuskyAttributeSet>(AttributeSet);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair, AS](const FOnAttributeChangeData& Data)
		{
			FAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
			Info.AttributeValue = Pair.Value().GetNumericValue(AS);
			AttributeInfoDelegate.Broadcast(Info);
		}
	);
	}	

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	// Obtain AS
	UDuskyAttributeSet* AS = CastChecked<UDuskyAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
	
}
