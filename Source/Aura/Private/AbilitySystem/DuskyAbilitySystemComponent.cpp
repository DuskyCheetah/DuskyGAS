// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "DuskyGameplayTags.h"

void UDuskyAbilitySystemComponent::AbilityActorInfoSet()
{
	// Binding to EffectApplied function
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDuskyAbilitySystemComponent::EffectApplied);
	
}

void UDuskyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	// Iterate through provided StartupAbilities Array
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		// Create a local FGameplayAbilitySpec - passing in current index of StartupAbilities and a level.
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// Give character the current AbilitySpec
		//GiveAbility(AbilitySpec);
		// Another option is to grant the ability and activate it immediately. AbilitySpec cannot be const.
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UDuskyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

}
