// Copyright DuskyDev!


#include "AbilitySystem/Abilities/DuskyProjectileAbilityBase.h"

#include "Actor/DuskyProjectile.h"
#include "Interaction/CombatInterface.h"


void UDuskyProjectileAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Boolean tracking if we are "on" the server
	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		// We are on server...
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		// Create Local SpawnTransform & set = to Weapon/Body Spawn Location Socket
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// TODO: Set the projectile rotation
		
		// Spawn the projectile with it's many many inputs.
		ADuskyProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADuskyProjectile>(
			ProjectileClass,											 // The Class to be spawned
			SpawnTransform,												// Locally created transform
			GetOwningActorFromActorInfo(),							   // Obtain owner of this GameplayAbility
			Cast<APawn>(GetOwningActorFromActorInfo()),			  // Instigator of the GameplayAbility
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);		 // Collision Handling Policy

		// TODO: Give the projectile a GameplayEffectSpec for causing damage.
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	

	
}
