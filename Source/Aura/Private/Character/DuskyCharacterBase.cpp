// Copyright DuskyDev!


#include "Character/DuskyCharacterBase.h"


ADuskyCharacterBase::ADuskyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

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

