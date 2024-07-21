// Copyright DuskyDev!


#include "Actor/DuskyEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


ADuskyEffectActor::ADuskyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void ADuskyEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void ADuskyEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
		
	// Use ASC getter from EPIC ASCBlueprintLibrary Func "GetAbilitySystemComponent"
	// and store in a ASC Ptr.
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// Ensure overlapping actor has an ASC
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	// Create GameEffectContextHandle - a wrapper for the context to be polymorphic and passed around easily.
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// Creates and stores the creator of this effect - so we can keep track of who/what caused this effect.
	EffectContextHandle.AddSourceObject(this);
	// Create SpecHandle (Wrapper for EffectSpec) for gameplay effect.
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	// This needs a Spec - not SpecHandle. Also requires it by const reference - not pointer
	// We access the data from SpecHandle & call .get() to get the raw pointer
	// Then dereference the pointer with the prefixed "*"
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Obtain Duration policy from EffectSpecHandle. "Def" is the member holding the policy.
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Store the TargetASC and EffectHandle in a map - for reference
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}

	// If GE = Instant AND DestroyOnEffectApp boolean is set to true, destroy effect actor
	if (bDestroyOnEffectApplication && !bIsInfinite)
	{
		Destroy();
	}
}

void ADuskyEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void ADuskyEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("Enemy")) && !bApplyEffectsToEnemies) return;
	
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Obtain TargetsASC
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// Create Array to store handles to remove from TMap through Loop
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			// Check if TargetASC's is the one that applied effect
			if (TargetASC == HandlePair.Value)
			{
				// Remove Active Effect -- Second argument is # of stacks to remove
				// -1 = all stacks removed
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				// Add key to Garbage Array for removal after loop
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		// Loop through the Garbage array
		for (FActiveGameplayEffectHandle&  Handle : HandlesToRemove)
		{
			// Safely remove antiquated handle from TMap
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}


