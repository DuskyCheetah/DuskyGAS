// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemGlobals.h"
#include "DuskyAbilityTypes.h"

FGameplayEffectContext* UDuskyAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDuskyGameplayEffectContext();
}
