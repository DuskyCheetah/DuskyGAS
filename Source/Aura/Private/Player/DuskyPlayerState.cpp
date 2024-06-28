// Copyright DuskyDev!


#include "Player/DuskyPlayerState.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "Net/UnrealNetwork.h"

ADuskyPlayerState::ADuskyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDuskyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDuskyAttributeSet>("AttrbuteSet");
	
	// How often server will try to update clients. (Multiplayer)
	NetUpdateFrequency = 100.f;
	
}

void ADuskyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register Level to be replicated
	DOREPLIFETIME(ADuskyPlayerState, Level);
}

UAbilitySystemComponent* ADuskyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADuskyPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
