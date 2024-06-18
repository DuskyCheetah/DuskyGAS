// Copyright DuskyDev!


#include "Player/DuskyPlayerState.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAttributeSet.h"

ADuskyPlayerState::ADuskyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDuskyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDuskyAttributeSet>("AttrbuteSet");
	
	// How often server will try to update clients. (Multiplayer)
	NetUpdateFrequency = 100.f;
	
}

UAbilitySystemComponent* ADuskyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
