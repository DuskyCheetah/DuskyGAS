// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DuskyGameplayAbility.h"
#include "DuskyProjectileAbilityBase.generated.h"

class ADuskyProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UDuskyProjectileAbilityBase : public UDuskyGameplayAbility
{
	GENERATED_BODY()
public:

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	// Member to Create ProjectileClass to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADuskyProjectile> ProjectileClass;
};
