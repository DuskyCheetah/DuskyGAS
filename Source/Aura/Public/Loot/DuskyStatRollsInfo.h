// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DuskyStatRollsInfo.generated.h"

UENUM()
enum class EStatTiers : uint8
{
	T0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7
};

UENUM()
enum class StatType : uint8
{
	Prefix,
	Suffix
};

USTRUCT(BlueprintType)
struct FStatRollInfo
{
	GENERATED_BODY()

	// Matching GameplayTag to Stat
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	// Stat Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	// Prefix or Suffix Designator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<StatType> Type; 

	// Roll Tier and Corresponding Maximum Roll Value
	UPROPERTY(EditDefaultsOnly)
	TMap<EStatTiers, float> StatTiers;
};

/**
 * 
 */
UCLASS()
class AURA_API UDuskyStatRollsInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	// List of AttributeInfo
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FStatRollInfo> StatRollInformation;
};
