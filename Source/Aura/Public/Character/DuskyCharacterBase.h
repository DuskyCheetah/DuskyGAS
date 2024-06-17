// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DuskyCharacterBase.generated.h"

// Prevents class from being added to any level
UCLASS(Abstract)
class AURA_API ADuskyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADuskyCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
