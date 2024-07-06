// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyClassInfo.generated.h"

class UGameplayEffect;

// Enum declaring RPG Classes w/i game
UENUM(BlueprintType)
enum class EEnemyClass : uint8
{
	// Enemy Classes
	Enemy,
	Elite,
	Boss
};

// Struct declaring specific class info
USTRUCT(BlueprintType)
struct FEnemyClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> EnemyAttributes;
	
};

/**
 * 
 */
UCLASS()
class AURA_API UEnemyClassInfo : public UDataAsset
{
	GENERATED_BODY()

	// Mapping Character Class to it's DefaultInfo
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<EEnemyClass, FEnemyClassDefaultInfo> EnemyClassInformation;
	
	// Getter for ClassDefaultInfo when passed a specific Class
	FEnemyClassDefaultInfo GetEnemyClassDefaultInfo(EEnemyClass EnemyClass);
};
