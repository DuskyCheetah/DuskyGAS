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
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	// This needs a Spec - not SpecHandle. Also requires it by const reference - not pointer
	// We access the data from SpecHandle & call .get() to get the raw pointer
	// Then dereference the pointer with the prefixed "*"
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


