// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  DuskyGameplayTags
 *
 *  Singleton containing native Gameplay Tags
 */

struct FDuskyGameplayTags
{
public:
	static const FDuskyGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// Begin Core Tags
	FGameplayTag Attributes_Core_Strength;
	FGameplayTag Attributes_Core_Vitality;
	FGameplayTag Attributes_Core_Intelligence;
	FGameplayTag Attributes_Core_Dexterity;
	// End Core Tags

	// Begin Vital Tags
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_MaxMana;
	// End Vital Tags

	// Begin Defensive Tags
	FGameplayTag Attributes_Defensive_Armor;
	FGameplayTag Attributes_Defensive_BlockChance;
	FGameplayTag Attributes_Defensive_DodgeChance;
	// End Defensive Tags

	// Begin Recovery Tags
	FGameplayTag Attributes_Recovery_HealthRegen;
	FGameplayTag Attributes_Recovery_ManaRegen;
	FGameplayTag Attributes_Recovery_Leech;
	FGameplayTag Attributes_Recovery_LifeOnHit;
	// End Recovery Tags

	// Begin Offensive Tags
	FGameplayTag Attributes_Offensive_CriticalHitChance;
	FGameplayTag Attributes_Offensive_CriticalHitDamage;
	FGameplayTag Attributes_Offensive_ActionSpeed;
	FGameplayTag Attributes_Offensive_AttackPower;
	FGameplayTag Attributes_Offensive_SpellPower;
	FGameplayTag Attributes_Offensive_Area;
	FGameplayTag Attributes_Offensive_Multicast;
	FGameplayTag Attributes_Offensive_Range;
	FGameplayTag Attributes_Offensive_ExtraProj;
	FGameplayTag Attributes_Offensive_ArmorPen;
	// End Offensive Tags

	// Begin Utility Tags
	FGameplayTag Attributes_Utility_MovementSpeed;
	FGameplayTag Attributes_Utility_CooldownReduction;
	FGameplayTag Attributes_Utility_PickupRadius;
	FGameplayTag Attributes_Utility_GoldFind;
	FGameplayTag Attributes_Utility_DashCount;
	// End Utility Tags
protected:

private:
	static FDuskyGameplayTags GameplayTags;
};