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
	
	// Begin Core Native Tag Register
	GameplayTags.Attributes_Core_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Strength"));
	GameplayTags.Attributes_Core_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Vitality"));
	GameplayTags.Attributes_Core_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Intelligence"));
	GameplayTags.Attributes_Core_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Core.Dexterity"));
	// End Core Native Tag Register

	// Begin Vital Native Tag Register
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"));
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"));
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"));
	// End Vital Native Tag Register

	// Begin Defensive Native Tag Register
	GameplayTags.Attributes_Defensive_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.Armor"));
	GameplayTags.Attributes_Defensive_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.BlockChance"));
	GameplayTags.Attributes_Defensive_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Defensive.DodgeChance"));
	// End Defensive Native Tag Register

	// Begin Recovery Native Tag Register
	GameplayTags.Attributes_Recovery_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.HealthRegen"));
	GameplayTags.Attributes_Recovery_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.ManaRegen"));
	GameplayTags.Attributes_Recovery_Leech = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.Leech"));
	GameplayTags.Attributes_Recovery_LifeOnHit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Recovery.LifeOnHit"));
	// End Recovery Native Tag Register

	// Begin Offensive Native Tag Register
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
	// End Offensive Native Tag Register

	// Begin Utility Native Tag Register
	GameplayTags.Attributes_Utility_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.MovementSpeed"));
	GameplayTags.Attributes_Utility_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.CooldownReduction"));
	GameplayTags.Attributes_Utility_PickupRadius = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.PickupRadius"));
	GameplayTags.Attributes_Utility_GoldFind = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.GoldFind"));
	GameplayTags.Attributes_Utility_DashCount = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Utility.DashCount"));
	// End Utility Native Tag Register

	/*
	 *		INPUT TAG REGISTER
	 */ 
	
	// Begin Input Native Tag Register
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for Key 1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for Key 2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for Key 3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for Key 4"));
	// End Input Native Tag Register

	// Damage Tag
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
}
