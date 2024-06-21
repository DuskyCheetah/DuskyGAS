// Copyright DuskyDev!


#include "Player/DuskyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

ADuskyPlayerController::ADuskyPlayerController()
{
	bReplicates = true;
}

void ADuskyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void ADuskyPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 *	Line trace from cursor. There are several scenarios:
	 *		A. LastActor is null && ThisActor is null
	 *			- Do Nothing
	 *		B. LastActor is null && ThisActor is valid
	 *			- Highlight ThisActor
	 *		C. LastActor is valid && ThisActor is null
	 *			- UnHighlight LastActor
	 *		D. Both actors are valid, but LastActor != ThisActor
	 *			- UnHighlight LastActor, and Highlight ThisActor
	 *		E. Both actors are valid and are the same actor
	 *			- Do Nothing
	 **/

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHightlightActor();
		}
		else // Both Actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHightlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}


void ADuskyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Check if DuskyContext is null or not. Prevent crashing.
	check(DuskyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		// Add mapping context so PlayerController can retrieve required data.
		Subsystem->AddMappingContext(DuskyContext, 0);
	}


	// Always show mouse cursor in viewport
	bShowMouseCursor = true;
	// Select which cursor to display
	DefaultMouseCursor = EMouseCursor::Default;

	// Do not lock cursor to viewport
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Do not hide cursor during mouse capture (i.e. whilst mouse button down)
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ADuskyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind the Move function to the Move Input Action
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADuskyPlayerController::Move);
}

void ADuskyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// Cast the InputActionValue to FVector2D - the form in which we need it.
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Obtain forward vector in relation to YawRotation vector.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// Obtain right vector in relation to YawRotation vector.
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// Add the forward to backward movement based on Y axis.
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		// Add the left to right movement based on the X axis.
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

