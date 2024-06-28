// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Character/DuskyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "DuskyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ADuskyEnemy : public ADuskyCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ADuskyEnemy();

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHightlightActor() override;
	// Enemy Interface

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	// Combat Interface
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;


	
};


