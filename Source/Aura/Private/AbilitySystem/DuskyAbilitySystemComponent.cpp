// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "DuskyGameplayTags.h"
#include "AbilitySystem/Abilities/DuskyGameplayAbility.h"

void UDuskyAbilitySystemComponent::AbilityActorInfoSet()
{
	// Binding to EffectApplied function
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDuskyAbilitySystemComponent::EffectApplied);
	
}

void UDuskyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	// Iterate through provided StartupAbilities Array
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{

		// Create a local FGameplayAbilitySpec - passing in current index of StartupAbilities and a level.
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// If any ability is of UDuskyGameplayAbility (i.e. the Cast is successful)
		if (const UDuskyGameplayAbility* DuskyAbility = Cast<UDuskyGameplayAbility>(AbilitySpec.Ability))
		{
			// Add Gameplay Tag to StartupInputTag
			// This is a method of changing inputs at runtime.
			AbilitySpec.DynamicAbilityTags.AddTag(DuskyAbility->StartupInputTag);
			// Give character the current AbilitySpec
			GiveAbility(AbilitySpec);
			// Another option is to grant the ability and activate it immediately. AbilitySpec cannot be const.
			//GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UDuskyAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	// Validation check for InputTag
	if (!InputTag.IsValid()) return;

	// Iterate through the result of the ActivatableAbilities GETTER
	for (FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		// Match tags w/i AbilitySpec to passed in Tag.
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// Boolean tracking if Input has been pressed.
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				// Try to activate the ability
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UDuskyAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	// Validation check for InputTag
	if (!InputTag.IsValid()) return;

	// Iterate through the result of the ActivatableAbilities GETTER
	for (FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		// Match tags w/i AbilitySpec to passed in Tag.
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			// Boolean tracking if Input has been released.
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UDuskyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);

}
