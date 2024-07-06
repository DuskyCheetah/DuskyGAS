// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DuslyGameModeBase.generated.h"

class UEnemyClassInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
// TODO:: Find a way to fix this typo without breaking the whole fucking thing lul.
class AURA_API ADuslyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Enemy Class Defaults")
	TObjectPtr<UEnemyClassInfo> EnemyClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
