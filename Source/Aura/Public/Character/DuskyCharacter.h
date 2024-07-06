// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
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

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	// Combat Interface

protected:
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Mage;
	
private:
	virtual void InitAbilityActorInfo() override;
};
