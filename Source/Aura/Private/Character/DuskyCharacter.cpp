// Copyright DuskyDev!


#include "Character/DuskyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ADuskyCharacter::ADuskyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// further tweak this within the editor
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);

	// Typical params for top-down game.
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	// 

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}
