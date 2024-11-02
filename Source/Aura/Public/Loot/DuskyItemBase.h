// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DuskyItemBase.generated.h"

// Rarity types for items
enum EItemRarity
{
	Normal,
	Magical,
	Rare,
	Legendary,
	Unique
};

// Inventory type of the item to be used for where to store said item
enum EInventoryType
{
	Currency,
	Material,
	Gem,
	SlotItem
};

UCLASS()
class AURA_API ADuskyItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADuskyItemBase();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	bool bCanBeEquipped = false;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	bool bIsEquipped = false;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	bool bCanBeSold = false;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	bool bCanStack = false;

	// Add Item Name Variable
	
	// Rarity of the item set on construction - normal by default.
	EItemRarity Rarity = Normal;

	// 1 by default - item tooltip will not show a requirement if 1.
	int LevelRequirement = 1;

	// Item Level used to scale stats
	int ItemLevel = 1;

protected:
	virtual void BeginPlay() override;


};
