// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Character/DuskyCharacterBase.h"
#include "DuskyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ADuskyCharacter : public ADuskyCharacterBase
{
	GENERATED_BODY()
public:
	ADuskyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
};
