// Copyright DuskyDev!


#include "Character/DuskyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "DuskyGameplayTags.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"


ADuskyCharacterBase::ADuskyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set collision to ignore camera for both the capsule and mesh of characters
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ADuskyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ADuskyCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ADuskyCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void ADuskyCharacterBase::MulticastHandleDeath_Implementation()
{
	// Drop Weapon and bounce around upon death (All Clients)
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// Rag doll mesh upon death (All Clients)
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bDead = true;
}

void ADuskyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ADuskyCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FDuskyGameplayTags& GameplayTags = FDuskyGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}

	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	return FVector();

}

bool ADuskyCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ADuskyCharacterBase::GetAvatar_Implementation() 
{
	return this;
}

TArray<FTaggedMontage> ADuskyCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
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

}

void ADuskyCharacterBase::AddCharacterAbilities() const
{
	// Obtain Characters ASC
	UDuskyAbilitySystemComponent* DuskyASC = CastChecked<UDuskyAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	DuskyASC->AddCharacterAbilities(StartupAbilities);
}



