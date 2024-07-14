// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "DuskyAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDuskyAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
