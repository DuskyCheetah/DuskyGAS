// Copyright DuskyDev!


#include "AbilitySystem/DuskyAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "DuskyGameplayTags.h"

UDuskyAttributeSet::UDuskyAttributeSet()
{
	const FDuskyGameplayTags& GameplayTags = FDuskyGameplayTags::Get();

	// Begin Add Core Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Core_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Core_Vitality, GetVitalityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Core_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Core_Dexterity, GetDexterityAttribute);
	// End Add Core Stats to Map

	// Begin Add Vital Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_Mana, GetManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Vital_MaxMana, GetMaxManaAttribute);
	// End Add Vital Stats to Map

	// Begin Add Defensive Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Defensive_DodgeChance, GetDodgeChanceAttribute);
	// End Add Defensive Stats to Map

	// Begin Add Recovery Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Recovery_HealthRegen, GetHealthRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Recovery_ManaRegen, GetManaRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Recovery_Leech, GetLeechAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Recovery_LifeOnHit, GetLifeOnHitAttribute);
	// End Add Recovery Stats to Map

	// Begin Add Offensive Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_ActionSpeed, GetActionSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_AttackPower, GetAttackPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_SpellPower, GetSpellPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_Area, GetAreaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_Range, GetRangeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_Multicast, GetMulticastAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_ExtraProj, GetExtraProjAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Offensive_ArmorPen, GetArmorPenAttribute);
	// End Add Offensive Stats to Map

	// Begin Add Utility Stats to Map
	TagsToAttributes.Add(GameplayTags.Attributes_Utility_MovementSpeed, GetMovementSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Utility_CooldownReduction, GetCooldownReductionAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Utility_PickupRadius, GetPickupRadiusAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Utility_GoldFind, GetGoldFindAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Utility_DashCount, GetDashCountAttribute);
	// End Add Utility Stats to Map

}

void UDuskyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register every replicated attribute

	// Begin Core Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	// End Core Attribute Register
	
	// Begin Vital Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	// End Vital Attribute Register

	// Begin Defensive Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, DodgeChance, COND_None, REPNOTIFY_Always);
	// End Defensive Attribute Register

	// Begin Recovery Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Leech, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, LifeOnHit, COND_None, REPNOTIFY_Always);
	// End Recovery Attribute Register

	// Begin Offensive Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, ActionSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, SpellPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Area, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Multicast, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Range, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, ExtraProj, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, ArmorPen, COND_None, REPNOTIFY_Always);
	// End Offensive Attribute Register

	// Begin Utility Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, PickupRadius, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, GoldFind, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, DashCount, COND_None, REPNOTIFY_Always);
	// End Utility Attribute Register
}

// Epic recommends to stick with just clamping attribute in this method. Do not fire off events.
void UDuskyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		// Clamp Health change to be between 0 and MaxHealth Value
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		// Clamp Mana change to be between 0 and MaxMana Value
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}

}

void UDuskyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	
	// Source = Causer of Effect -- Target = Target of Effect (Owner of this AttributeSet)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	// Obtain Source ASC
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		// Obtain Source AvatarActor
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		// Obtain Source Controller
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		// Attempt to Obtain Source Controller if above returns null
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		// Attempt to Obtain Source Character from SourceController
		if (Props.SourceController)
		{
			// Obtain Source Character
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}

}

void UDuskyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// Proper Clamping of the Health attribute via SETTING the attribute
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	// Proper Clamping of the Mana attribute via SETTING the attribute
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();	// Catch the value of Incoming Damage
		SetIncomingDamage(0.f);	// Reset it to zero

		if (LocalIncomingDamage > 0.f)	// Only need to act if incoming damage was > zero
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
		}
	}
}

// Begin Core OnRep Definitions
void UDuskyAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Health, OldStrength);
}
void UDuskyAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Health, OldVitality);
}
void UDuskyAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Health, OldIntelligence);
}
void UDuskyAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Health, OldDexterity);
}
// End Core OnRep Definitions

// Begin Vital OnRep Definitions
void UDuskyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Health, OldHealth);
}
void UDuskyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxHealth, OldMaxHealth);
}
void UDuskyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, Mana, OldMana);
}
void UDuskyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldMaxMana);
}
// End Vital OnRep Definitions

// Begin Defensive OnRep Definitions
void UDuskyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldArmor);
}
void UDuskyAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldBlockChance);
}
void UDuskyAttributeSet::OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldDodgeChance);
}
// End Defensive OnRep Definitions

// Begin Recovery OnRep Definitions
void UDuskyAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldHealthRegen);
}
void UDuskyAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldManaRegen);
}
void UDuskyAttributeSet::OnRep_Leech(const FGameplayAttributeData& OldLeech) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldLeech);
}
void UDuskyAttributeSet::OnRep_LifeOnHit(const FGameplayAttributeData& OldLifeOnHit) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldLifeOnHit);
}
// End Recovery OnRep Definitions

// Begin Offensive OnRep Definitions
void UDuskyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldCriticalHitChance);
}
void UDuskyAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldCriticalHitDamage);
}
void UDuskyAttributeSet::OnRep_ActionSpeed(const FGameplayAttributeData& OldActionSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldActionSpeed);
}
void UDuskyAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldAttackPower);
}
void UDuskyAttributeSet::OnRep_SpellPower(const FGameplayAttributeData& OldSpellPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldSpellPower);
}
void UDuskyAttributeSet::OnRep_Area(const FGameplayAttributeData& OldArea) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldArea);
}
void UDuskyAttributeSet::OnRep_Multicast(const FGameplayAttributeData& OldMulticast) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldMulticast);
}
void UDuskyAttributeSet::OnRep_Range(const FGameplayAttributeData& OldRange) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldRange);
}
void UDuskyAttributeSet::OnRep_ExtraProj(const FGameplayAttributeData& OldExtraProj) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldExtraProj);
}
void UDuskyAttributeSet::OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldArmorPen);
}
// End Offensive OnRep Definitions

// Begin Utility OnRep Definitions
void UDuskyAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldMovementSpeed);
}
void UDuskyAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldCooldownReduction);
}
void UDuskyAttributeSet::OnRep_PickupRadius(const FGameplayAttributeData& OldPickupRadius) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldPickupRadius);
}
void UDuskyAttributeSet::OnRep_GoldFind(const FGameplayAttributeData& OldGoldFind) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldGoldFind);
}
void UDuskyAttributeSet::OnRep_DashCount(const FGameplayAttributeData& OldDashCount) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDuskyAttributeSet, MaxMana, OldDashCount);
}
// End Utility OnRep Definitions




