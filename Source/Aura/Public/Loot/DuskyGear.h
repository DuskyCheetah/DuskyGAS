// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Loot/DuskyItemBase.h"
#include "DuskyGear.generated.h"

enum EItemType
{
	Helm,
	Amulet,
	Shoulder,
	Cloak,
	Chest,
	Bracers,
	Gloves,
	Belt,
	Pants,
	Boots,
	Ring,
	OneHand,
	TwoHand,
	OffHand
	
};

/**
 * 
 */
UCLASS()
class AURA_API ADuskyGear : public ADuskyItemBase
{
	GENERATED_BODY()

	ADuskyGear();
	ADuskyGear(const EItemRarity Rarity, const int ItemLevel, const EItemType ItemType);

private:

	EItemType ItemType;

	UPROPERTY()
	TMap<FName, float> ItemSuffixOne;
};
