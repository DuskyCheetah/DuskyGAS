// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyClassInfo.generated.h"

class UGameplayAbility;
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

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> DerivedAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
};

/**
 * 
 */
UCLASS()
class AURA_API UEnemyClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	
	// Mapping Character Class to it's DefaultInfo
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<EEnemyClass, FEnemyClassDefaultInfo> EnemyClassInformation;

	// Common GameplayAbilities all enemies have.
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
	// Getter for ClassDefaultInfo when passed a specific Class
	FEnemyClassDefaultInfo GetEnemyClassDefaultInfo(EEnemyClass EnemyClass);


};
