// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DuskyStatRollsInfo.generated.h"

UENUM()
enum EStatRoll
{
	Strength,
	Vitality,
	Intelligence,
	Dexterity,
	MaxHealth,
	MaxMana,
	Armor,
	BlockChance,
	DodgeChance,
	FireResistance,
	FrostResistance,
	LightningResistance,
	CausticResistance,
	HealthRegen,
	ManaRegen,
	LifeOnHit,
	Leech,
	CriticalHitChance,
	CriticalHitDamage,
	ActionSpeed,
	AttackPower,
	SpellPower,
	Area,
	Multicast,
	Range,
	ExtraProj,
	ArmorPen,
	MovementSpeed,
	CooldownReduction,
	PickupRadius,
	GoldFind,
	DashCount,
};

UENUM()
enum EStatTiers 
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
enum EStatTypeRoll 
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
	TEnumAsByte<EStatRoll> Stat;

	// Prefix or Suffix Designator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EStatTypeRoll> Type;

	// Roll Tier and Corresponding Maximum Roll Value
	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EStatTiers>, float> StatTiers;
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
