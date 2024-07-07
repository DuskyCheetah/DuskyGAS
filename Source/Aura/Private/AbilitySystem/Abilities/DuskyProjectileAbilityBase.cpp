// Copyright DuskyDev!


#include "AbilitySystem/Abilities/DuskyProjectileAbilityBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/DuskyProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/DuskyGameplayTags.h"


void UDuskyProjectileAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	

	
}

void UDuskyProjectileAbilityBase::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Boolean tracking if we are "on" the server
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		// We are on server...
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		// Vector from SocketLocation (SOURCE) to ProjectileTargetLocation (TARGET)
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		// Set pitch = 0 so projectiles fly parallel to the ground.
		Rotation.Pitch = 0.f;

		// Create Local SpawnTransform & set = to Weapon/Body Spawn Location Socket
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		// Spawn the projectile with it's many many inputs.
		ADuskyProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADuskyProjectile>(
			ProjectileClass,											 // The Class to be spawned
			SpawnTransform,												// Locally created transform
			GetOwningActorFromActorInfo(),							   // Obtain owner of this GameplayAbility
			Cast<APawn>(GetOwningActorFromActorInfo()),			  // Instigator of the GameplayAbility
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);		 // Collision Handling Policy


		/*	DAMAGE HANDLING		*/
		
		// Obtain ASC
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		// Create EffectContextHandle to pass into SpecHandle.
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		// Filling out Data params of the ContextHandle for a learning exercise.
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);

		// Create GE SpecHandle for Damage
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		// Obtain Native Gameplay Tags
		FDuskyGameplayTags GameplayTags = FDuskyGameplayTags::Get();
		// Obtain AbilityLevel for magnitude application.
		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Firebolt Damage %f"), ScaledDamage));
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);
		// Assigned Projectiles SpecHandle to the created SpecHandle with DamageEffectClass GE.
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		/*	DAMAGE HANDLING		*/

		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
