// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemComponent.h"

void UDuskyAbilitySystemComponent::AbilityActorInfoSet()
{
	// Binding to EffectApplied function
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDuskyAbilitySystemComponent::EffectApplied);
}

void UDuskyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

}
