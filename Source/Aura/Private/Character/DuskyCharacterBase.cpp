// Copyright DuskyDev!


#include "Character/DuskyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


ADuskyCharacterBase::ADuskyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set collision to ignore camera for both the capsule and mesh of characters
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ADuskyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADuskyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ADuskyCharacterBase::GetCombatSocketLocation()
{
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void ADuskyCharacterBase::InitAbilityActorInfo()
{
}

void ADuskyCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ADuskyCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultCoreAttributes, 1.f);
	ApplyEffectToSelf(DefaultDerivedAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ADuskyCharacterBase::AddCharacterAbilities()
{
	// Obtain Characters ASC
	UDuskyAbilitySystemComponent* DuskyASC = CastChecked<UDuskyAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	DuskyASC->AddCharacterAbilities(StartupAbilities);
}



