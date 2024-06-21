// Copyright DuskyDev!


#include "AbilitySystem/DuskyAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDuskyAttributeSet::UDuskyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(200.f);
	InitMaxMana(200.f);
}

void UDuskyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register every replicated attribute

	// Begin Vital Attribute Register
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDuskyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	// End Vital Attribute Register
}

// Begin Vital Attribute Definitions
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
// End Vital Attribute Definitions
