// Copyright DuskyDev!


#include "Character/DuskyEnemy.h"

#include "Aura/Aura.h"

ADuskyEnemy::ADuskyEnemy()
{
	// Change mesh default collision setting for visibility to Block
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
