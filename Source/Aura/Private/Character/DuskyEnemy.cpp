// Copyright DuskyDev!


#include "Character/DuskyEnemy.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "Aura/Aura.h"
#include "UObject/ReferenceChainSearch.h"

ADuskyEnemy::ADuskyEnemy()
{
	// Change mesh default collision setting for visibility to Block
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDuskyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UDuskyAttributeSet>("AttrbuteSet");
}

void ADuskyEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ADuskyEnemy::UnHightlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ADuskyEnemy::GetPlayerLevel()
{
	return Level;
}

void ADuskyEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

}

void ADuskyEnemy::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDuskyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
