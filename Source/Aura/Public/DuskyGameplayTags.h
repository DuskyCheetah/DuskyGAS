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

	/*
	 *		ATTRIBUTE TAGS
	 */ 
	
	// Core Tags
	FGameplayTag Attributes_Core_Strength;
	FGameplayTag Attributes_Core_Vitality;
	FGameplayTag Attributes_Core_Intelligence;
	FGameplayTag Attributes_Core_Dexterity;


	// Vital Tags
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_MaxHealth;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_MaxMana;


	// Defensive Tags
	FGameplayTag Attributes_Defensive_Armor;
	FGameplayTag Attributes_Defensive_BlockChance;
	FGameplayTag Attributes_Defensive_DodgeChance;


	// Damage Resistances
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Frost;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Physical;
	FGameplayTag Attributes_Resistance_Caustic;

	
	// Recovery Tags
	FGameplayTag Attributes_Recovery_HealthRegen;
	FGameplayTag Attributes_Recovery_ManaRegen;
	FGameplayTag Attributes_Recovery_Leech;
	FGameplayTag Attributes_Recovery_LifeOnHit;


	// Offensive Tags
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


	// Utility Tags
	FGameplayTag Attributes_Utility_MovementSpeed;
	FGameplayTag Attributes_Utility_CooldownReduction;
	FGameplayTag Attributes_Utility_PickupRadius;
	FGameplayTag Attributes_Utility_GoldFind;
	FGameplayTag Attributes_Utility_DashCount;


	/*
	*		SET BY CALLER TAGS
	*/

	// SetByCaller Core Tags
	FGameplayTag SetByCaller_Core_Strength;
	FGameplayTag SetByCaller_Core_Vitality;
	FGameplayTag SetByCaller_Core_Intelligence;
	FGameplayTag SetByCaller_Core_Dexterity;


	// SetByCaller Vital Tags
	FGameplayTag SetByCaller_Vital_Health;
	FGameplayTag SetByCaller_Vital_MaxHealth;
	FGameplayTag SetByCaller_Vital_Mana;
	FGameplayTag SetByCaller_Vital_MaxMana;


	// SetByCaller Defensive Tags
	FGameplayTag SetByCaller_Defensive_Armor;
	FGameplayTag SetByCaller_Defensive_BlockChance;
	FGameplayTag SetByCaller_Defensive_DodgeChance;


	// SetByCaller Damage Resistances
	FGameplayTag SetByCaller_Resistance_Fire;
	FGameplayTag SetByCaller_Resistance_Frost;
	FGameplayTag SetByCaller_Resistance_Lightning;
	FGameplayTag SetByCaller_Resistance_Physical;
	FGameplayTag SetByCaller_Resistance_Caustic;

	
	// SetByCaller Recovery Tags
	FGameplayTag SetByCaller_Recovery_HealthRegen;
	FGameplayTag SetByCaller_Recovery_ManaRegen;
	FGameplayTag SetByCaller_Recovery_Leech;
	FGameplayTag SetByCaller_Recovery_LifeOnHit;


	// SetByCaller Offensive Tags
	FGameplayTag SetByCaller_Offensive_CriticalHitChance;
	FGameplayTag SetByCaller_Offensive_CriticalHitDamage;
	FGameplayTag SetByCaller_Offensive_ActionSpeed;
	FGameplayTag SetByCaller_Offensive_AttackPower;
	FGameplayTag SetByCaller_Offensive_SpellPower;
	FGameplayTag SetByCaller_Offensive_Area;
	FGameplayTag SetByCaller_Offensive_Multicast;
	FGameplayTag SetByCaller_Offensive_Range;
	FGameplayTag SetByCaller_Offensive_ExtraProj;
	FGameplayTag SetByCaller_Offensive_ArmorPen;


	// SetByCaller Utility Tags
	FGameplayTag SetByCaller_Utility_MovementSpeed;
	FGameplayTag SetByCaller_Utility_CooldownReduction;
	FGameplayTag SetByCaller_Utility_PickupRadius;
	FGameplayTag SetByCaller_Utility_GoldFind;
	FGameplayTag SetByCaller_Utility_DashCount;

	
	/*
	*		DAMAGE TAGS
	*/
	
	// Damage / Damage Types Tags
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Frost;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Caustic;
	
	// Map Damage Types to respective Game Type Resistance
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResists;
	


	// Ability Tags
	FGameplayTag Abilities_Attack;

	// Attack Montage Tags 
	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_LeftHand;
	FGameplayTag Montage_Attack_RightHand;

	
	// Effect Tags
	FGameplayTag Effects_HitReact;
	
	/*
	 *		INPUT TAGS
	 */ 
	
	// Input Tags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;


	/*
	 *		EQUIPMENT TAGS
	 */ 

	// Equipped Gear Tags
	FGameplayTag Equipment_Slot_Head;
	FGameplayTag Equipment_Slot_Shoulder;
	FGameplayTag Equipment_Slot_Amulet;
	FGameplayTag Equipment_Slot_Cloak;
	FGameplayTag Equipment_Slot_Chest;
	FGameplayTag Equipment_Slot_Bracers;
	FGameplayTag Equipment_Slot_Gloves;
	FGameplayTag Equipment_Slot_Belt;
	FGameplayTag Equipment_Slot_Pants;
	FGameplayTag Equipment_Slot_Boots;
	FGameplayTag Equipment_Slot_Ring;
	FGameplayTag Equipment_Slot_MainHand;
	FGameplayTag Equipment_Slot_OffHand;


private:
	static FDuskyGameplayTags GameplayTags;
};