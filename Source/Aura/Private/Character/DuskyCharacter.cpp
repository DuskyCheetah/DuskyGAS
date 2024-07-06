// Copyright DuskyDev!


#include "Character/DuskyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DuskyPlayerController.h"
#include "Player/DuskyPlayerState.h"
#include "UI/HUD/DuskyHUD.h"

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
	// Granting applicable abilities to character.
	AddCharacterAbilities();
	
}

void ADuskyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor for the client.
	InitAbilityActorInfo();
}

int32 ADuskyCharacter::GetPlayerLevel()
{
	const ADuskyPlayerState* DuskyPlayerState = GetPlayerState<ADuskyPlayerState>();
	check(DuskyPlayerState);
	return DuskyPlayerState->GetPlayerLevel();
}

void ADuskyCharacter::InitializeDefaultAttributes() const
{
	// Obtain PlayerState to retrieve Player Level
	const ADuskyPlayerState* DuskyPlayerState = GetPlayerState<ADuskyPlayerState>();
	check(DuskyPlayerState);
	int32 Level = DuskyPlayerState->GetPlayerLevel();
	
	UDuskyAbilitySystemLibrary::InitializePlayerDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ADuskyCharacter::InitAbilityActorInfo()
{
	ADuskyPlayerState* DuskyPlayerState = GetPlayerState<ADuskyPlayerState>();
	check(DuskyPlayerState);
	DuskyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DuskyPlayerState, this);
	Cast<UDuskyAbilitySystemComponent>(DuskyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = DuskyPlayerState->GetAbilitySystemComponent();
	AttributeSet = DuskyPlayerState->GetAttributeSet();

	// IF the player controller is not null - which it will be in some situations within multiplayer settings
	if (ADuskyPlayerController* DuskyPlayerController = Cast<ADuskyPlayerController>(GetController()))
	{
		// IF the DuskyHUD widget isn't null - which it will be in some situations within multiplayer settings
		if (ADuskyHUD* DuskyHUD = Cast<ADuskyHUD>(DuskyPlayerController->GetHUD()))
		{
			// Init the overlay with the 4 key variables.
			DuskyHUD->InitOverlay(DuskyPlayerController, DuskyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
