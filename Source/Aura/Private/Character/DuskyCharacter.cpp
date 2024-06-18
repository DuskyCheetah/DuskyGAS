// Copyright DuskyDev!


#include "Character/DuskyCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DuskyPlayerState.h"

ADuskyCharacter::ADuskyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Further tweak this within the editor
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);

	// Typical params for top-down game.
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	// 

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}

void ADuskyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server.
	InitAbilityActorInfo();
	
}

void ADuskyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor for the client.
	InitAbilityActorInfo();
}

void ADuskyCharacter::InitAbilityActorInfo()
{
	ADuskyPlayerState* DuskyPlayerState = GetPlayerState<ADuskyPlayerState>();
	check(DuskyPlayerState);
	DuskyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DuskyPlayerState, this);
	AbilitySystemComponent = DuskyPlayerState->GetAbilitySystemComponent();
	AttributeSet = DuskyPlayerState->GetAttributeSet();
}
