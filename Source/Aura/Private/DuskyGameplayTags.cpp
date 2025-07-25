// Copyright DuskyDev!


#include "DuskyGameplayTags.h"
#include "GameplayTagsManager.h"

// Fully declare the static variable
FDuskyGameplayTags FDuskyGameplayTags::GameplayTags;

void FDuskyGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 *		ATTRIBUTE TAG REGISTER
	 */ 
	
	// Core Native Tag Register
	GameplayTags.Attributes_Core_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Strength"));
	GameplayTags.Attributes_Core_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Vitality"));
	GameplayTags.Attributes_Core_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Intelligence"));
	GameplayTags.Attributes_Core_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Dexterity"));

	// Vital Native Tag Register
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"));
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"));
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"));


	// Defensive Native Tag Register
	GameplayTags.Attributes_Defensive_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.Armor"));
	GameplayTags.Attributes_Defensive_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.BlockChance"));
	GameplayTags.Attributes_Defensive_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.DodgeChance"));


	// Resistance Native Tag Register
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to the Fire Damage Type"));
	GameplayTags.Attributes_Resistance_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Frost"), FString("Resistance to the Frost Damage Type"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to the Lightning Damage Type"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to the Physical Damage Type"));
	GameplayTags.Attributes_Resistance_Caustic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Caustic"), FString("Resistance to the Caustic Damage Type"));

	
	// Recovery Native Tag Register
	GameplayTags.Attributes_Recovery_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.HealthRegen"));
	GameplayTags.Attributes_Recovery_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.ManaRegen"));
	GameplayTags.Attributes_Recovery_Leech = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.Leech"));
	GameplayTags.Attributes_Recovery_LifeOnHit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.LifeOnHit"));


	// Offensive Native Tag Register
	GameplayTags.Attributes_Offensive_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.CriticalHitChance"));
	GameplayTags.Attributes_Offensive_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.CriticalHitDamage"));
	GameplayTags.Attributes_Offensive_ActionSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.ActionSpeed"));
	GameplayTags.Attributes_Offensive_AttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.AttackPower"));
	GameplayTags.Attributes_Offensive_SpellPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.SpellPower"));
	GameplayTags.Attributes_Offensive_Area = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.Area"));
	GameplayTags.Attributes_Offensive_Multicast = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.Multicast"));
	GameplayTags.Attributes_Offensive_Range = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.Range"));
	GameplayTags.Attributes_Offensive_ExtraProj = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.ExtraProj"));
	GameplayTags.Attributes_Offensive_ArmorPen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Offensive.ArmorPen"));
	

	// Utility Native Tag Register
	GameplayTags.Attributes_Utility_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.MovementSpeed"));
	GameplayTags.Attributes_Utility_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.CooldownReduction"));
	GameplayTags.Attributes_Utility_PickupRadius = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.PickupRadius"));
	GameplayTags.Attributes_Utility_GoldFind = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.GoldFind"));
	GameplayTags.Attributes_Utility_DashCount = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.DashCount"));


	/*
	 *		SETBYCALLER TAG REGISTER
	 */ 
	
	// Core Native Tag Register
	GameplayTags.SetByCaller_Core_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Core.Strength"));
	GameplayTags.SetByCaller_Core_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Core.Vitality"));
	GameplayTags.SetByCaller_Core_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Core.Intelligence"));
	GameplayTags.SetByCaller_Core_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Core.Dexterity"));


	// Vital Native Tag Register
	GameplayTags.SetByCaller_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Vital.Health"));
	GameplayTags.SetByCaller_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Vital.MaxHealth"));
	GameplayTags.SetByCaller_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Vital.Mana"));
	GameplayTags.SetByCaller_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Vital.MaxMana"));


	// Defensive Native Tag Register
	GameplayTags.SetByCaller_Defensive_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Defensive.Armor"));
	GameplayTags.SetByCaller_Defensive_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Defensive.BlockChance"));
	GameplayTags.SetByCaller_Defensive_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Defensive.DodgeChance"));


	// Resistance Native Tag Register
	GameplayTags.SetByCaller_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Resistance.Fire"));
	GameplayTags.SetByCaller_Resistance_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Resistance.Frost"));
	GameplayTags.SetByCaller_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Resistance.Lightning"));
	GameplayTags.SetByCaller_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Resistance.Physical"));
	GameplayTags.SetByCaller_Resistance_Caustic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Resistance.Caustic"));

	
	// Recovery Native Tag Register
	GameplayTags.SetByCaller_Recovery_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Recovery.HealthRegen"));
	GameplayTags.SetByCaller_Recovery_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Recovery.ManaRegen"));
	GameplayTags.SetByCaller_Recovery_Leech = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Recovery.Leech"));
	GameplayTags.SetByCaller_Recovery_LifeOnHit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Recovery.LifeOnHit"));


	// Offensive Native Tag Register
	GameplayTags.SetByCaller_Offensive_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.CriticalHitChance"));
	GameplayTags.SetByCaller_Offensive_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.CriticalHitDamage"));
	GameplayTags.SetByCaller_Offensive_ActionSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.ActionSpeed"));
	GameplayTags.SetByCaller_Offensive_AttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.AttackPower"));
	GameplayTags.SetByCaller_Offensive_SpellPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.SpellPower"));
	GameplayTags.SetByCaller_Offensive_Area = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.Area"));
	GameplayTags.SetByCaller_Offensive_Multicast = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.Multicast"));
	GameplayTags.SetByCaller_Offensive_Range = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.Range"));
	GameplayTags.SetByCaller_Offensive_ExtraProj = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.ExtraProj"));
	GameplayTags.SetByCaller_Offensive_ArmorPen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Offensive.ArmorPen"));


	// Utility Native Tag Register
	GameplayTags.SetByCaller_Utility_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Utility.MovementSpeed"));
	GameplayTags.SetByCaller_Utility_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Utility.CooldownReduction"));
	GameplayTags.SetByCaller_Utility_PickupRadius = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Utility.PickupRadius"));
	GameplayTags.SetByCaller_Utility_GoldFind = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Utility.GoldFind"));
	GameplayTags.SetByCaller_Utility_DashCount = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("SetByCaller.Utility.DashCount"));

	

	/*
	 *		DAMAGE REGISTER
	 */ 
	
	// Damage / Damage Type Tags
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Frost"), FString("Frost Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Type"));
	GameplayTags.Damage_Caustic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Caustic"), FString("Caustic Damage Type"));

	/* Map each damage type to its respective damage type resistance */
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Frost, GameplayTags.Attributes_Resistance_Frost);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResists.Add(GameplayTags.Damage_Caustic, GameplayTags.Attributes_Resistance_Caustic);


	// Abilities Native Tag Register
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));


	// Attack Montage Native Tag Register
	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.Weapon"), FString("Montage for when an enemy attacks with a weapon"));
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.LeftHand"), FString("Montage for when an enemy attacks with their left hand"));
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.RightHand"), FString("Montage for when an enemy attacks with their right hand"));
	
	// Effect Native Tag Register
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Tag granted when Hit Reacting"));

	
	/*
	 *		INPUT TAG REGISTER
	 */ 
	
	// Input Native Tag Register
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for Key 1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for Key 2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for Key 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for Key 4"));


	/*
	 *		EQUIPMENT TAG REGISTER
	*/

	// Equipped Gear Tag Register
	GameplayTags.Equipment_Slot_Head = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Head"), FString("Tag for head slot of equipped gear"));
	GameplayTags.Equipment_Slot_Shoulder = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Shoulder"), FString("Tag for shoulder slot of equipped gear"));
	GameplayTags.Equipment_Slot_Amulet = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Amulet"), FString("Tag for amulet slot of equipped gear"));
	GameplayTags.Equipment_Slot_Cloak = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Cloak"), FString("Tag for cloak slot of equipped gear"));
	GameplayTags.Equipment_Slot_Chest = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Chest"), FString("Tag for chest slot of equipped gear"));
	GameplayTags.Equipment_Slot_Bracers = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Bracers"), FString("Tag for bracers slot of equipped gear"));
	GameplayTags.Equipment_Slot_Gloves = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Gloves"), FString("Tag for gloves slot of equipped gear"));
	GameplayTags.Equipment_Slot_Belt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Belt"), FString("Tag for belt slot of equipped gear"));
	GameplayTags.Equipment_Slot_Pants = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Pants"), FString("Tag for pants slot of equipped gear"));
	GameplayTags.Equipment_Slot_Boots = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Boots"), FString("Tag for boots slot of equipped gear"));
	GameplayTags.Equipment_Slot_Ring = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.Ring"), FString("Tag for ring slot of equipped gear"));
	GameplayTags.Equipment_Slot_MainHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.MainHand"), FString("Tag for main hand slot of equipped gear"));
	GameplayTags.Equipment_Slot_OffHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Equipment.Slot.OffHand"), FString("Tag for off hand slot of equipped gear"));


}
