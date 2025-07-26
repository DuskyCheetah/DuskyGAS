// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DuskyGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "DuskyDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDuskyDamageGameplayAbility : public UDuskyGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
protected:

	// Damage Gameplay Effect Class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	// TMap mapping all Damage Types to respective values.
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
