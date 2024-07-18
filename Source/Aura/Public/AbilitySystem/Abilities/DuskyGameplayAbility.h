// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DuskyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDuskyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;


};
