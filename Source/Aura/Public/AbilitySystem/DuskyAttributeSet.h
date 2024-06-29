// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DuskyAttributeSet.generated.h"

// Utilizing this macro to auto-generate the following four functions for each Attribute
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	// Source Pointers
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// Target Pointers
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


/**
 * 
 */
UCLASS()
class AURA_API UDuskyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UDuskyAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Don't fucking ask me this shit is so deep, I'm drowning in my own asshole.
	// but it is very nice.
	TMap<FGameplayTag, FGameplayAttribute(*)()> TagsToAttributes;
	
	
	/*
	 *	ATTRIBUTE DECLARATIONS
	 */
	
	// Begin Core Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Core Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Strength);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vitality, Category = "Core Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Vitality);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Core Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Intelligence);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Core Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Dexterity);
	// End Core Attributes
	//***************************************************************
	// Begin Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, MaxHealth);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, MaxMana);
	// End Vital Attributes
	//***************************************************************
	// Begin Defensive Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Defensive Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Armor);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Defensive Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, BlockChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DodgeChance, Category = "Defensive Attributes")
	FGameplayAttributeData DodgeChance;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, DodgeChance);
	// End Defensive Attributes
	//***************************************************************
	// Begin Recovery Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Recovery Attributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, HealthRegen);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "Recovery Attributes")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, ManaRegen);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Leech, Category = "Recovery Attributes")
	FGameplayAttributeData Leech;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Leech);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LifeOnHit, Category = "Recovery Attributes")
	FGameplayAttributeData LifeOnHit;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, LifeOnHit);
	// End Recovery Attributes
	//***************************************************************
	// Begin Offensive Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Offensive Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, CriticalHitChance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Offensive Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, CriticalHitDamage);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ActionSpeed, Category = "Offensive Attributes")
	FGameplayAttributeData ActionSpeed;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, ActionSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Offensive Attributes")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, AttackPower);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellPower, Category = "Offensive Attributes")
	FGameplayAttributeData SpellPower;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, SpellPower);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Area, Category = "Offensive Attributes")
	FGameplayAttributeData Area;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Area);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Multicast, Category = "Offensive Attributes")
	FGameplayAttributeData Multicast;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Multicast);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Range, Category = "Offensive Attributes")
	FGameplayAttributeData Range;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, Range);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ExtraProj, Category = "Offensive Attributes")
	FGameplayAttributeData ExtraProj;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, ExtraProj);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPen, Category = "Offensive Attributes")
	FGameplayAttributeData ArmorPen;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, ArmorPen);
	// End Offensive Attributes
	//***************************************************************
	// Begin Utility Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Utility Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, MovementSpeed);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Utility Attributes")
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, CooldownReduction);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PickupRadius, Category = "Utility Attributes")
	FGameplayAttributeData PickupRadius;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, PickupRadius);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GoldFind, Category = "Utility Attributes")
	FGameplayAttributeData GoldFind;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, GoldFind);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DashCount, Category = "Utility Attributes")
	FGameplayAttributeData DashCount;
	ATTRIBUTE_ACCESSORS(UDuskyAttributeSet, DashCount);
	// End Utility Attributes
	//***************************************************************

	/*
	 *	ONREP DECLARATIONS
	 */
	
	// Begin Core OnReps
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	// End Core OnReps
	//***************************************************************
	// Begin Vital OnReps
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	// End Vital OnReps
	//***************************************************************
	// Begin Defensive OnReps
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance) const;
	// End Defensive OnReps
	//***************************************************************
	// Begin Recovery OnReps
	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;
	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;
	UFUNCTION()
	void OnRep_Leech(const FGameplayAttributeData& OldLeech) const;
	UFUNCTION()
	void OnRep_LifeOnHit(const FGameplayAttributeData& OldLifeOnHit) const;
	// End Recovery OnReps
	//***************************************************************
	// Begin Offensive OnReps
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_ActionSpeed(const FGameplayAttributeData& OldActionSpeed) const;
	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const;
	UFUNCTION()
	void OnRep_SpellPower(const FGameplayAttributeData& OldSpellPower) const;
	UFUNCTION()
	void OnRep_Area(const FGameplayAttributeData& OldArea) const;
	UFUNCTION()
	void OnRep_Multicast(const FGameplayAttributeData& OldMulticast) const;
	UFUNCTION()
	void OnRep_Range(const FGameplayAttributeData& OldRange) const;
	UFUNCTION()
	void OnRep_ExtraProj(const FGameplayAttributeData& OldExtraProj) const;
	UFUNCTION()
	void OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen) const;
	// End Offensive OnReps
	//***************************************************************
	//Begin Utility OnReps
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const;
	UFUNCTION()
	void OnRep_PickupRadius(const FGameplayAttributeData& OldPickupRadius) const;
	UFUNCTION()
	void OnRep_GoldFind(const FGameplayAttributeData& OldGoldFind) const;
	UFUNCTION()
	void OnRep_DashCount(const FGameplayAttributeData& OldDashCount) const;
	// End Utility OnReps

	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
