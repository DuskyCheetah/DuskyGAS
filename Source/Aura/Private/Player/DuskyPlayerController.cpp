// Copyright DuskyDev!


#include "Player/DuskyPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DuskyGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/DuskyInputComponent.h"
#include "Interaction/EnemyInterface.h"

ADuskyPlayerController::ADuskyPlayerController()
{
	bReplicates = true;

	// Construct Spline Object
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ADuskyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

void ADuskyPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		// Location on Spline that's closest to the ControlledPawn
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		// Find direction of movement needed
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		// Set that movement in motion, baby!
		ControlledPawn->AddMovementInput(Direction);

		// Calculate Distance of the movement
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		// If Distance is less than the acceptance radius of movements
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			// Stop auto-running
			bAutoRunning = false;
		}
	}
}


void ADuskyPlayerController::CursorTrace()
{
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

void ADuskyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FDuskyGameplayTags::Get().InputTag_LMB))
	{
		// If ThisActor == true, we are hovering over enemy target - bTargeting = true
		// Else - bTargeting = false (No Target)
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}

}

void ADuskyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// If input held IS NOT LMB - Do yo thang, fire that bitch.
	if (!InputTag.MatchesTagExact(FDuskyGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	// if input IS LMB and we ARE Targeting - Do yo thang, fire that bitch.
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}	
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		// Input IS LMB - We are NOT Targeting
		// Character movement functionality.
		if (FollowTime <= ShortPressThreshold&& ControlledPawn)	// If input key was pressed longer than our custom set threshold or not
		{
			// Find path between characters current location & the determined move-to location
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				// Clear any previous Spline Points
				Spline->ClearSplinePoints();
				// Iterate through the NavPath
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					// Add the next Spline Point to the Movement Spline
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 12.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		// Resetting FollowTime && bTargeting for this input release cycle.
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ADuskyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// If input held IS NOT LMB - Do yo thang.
	if (!InputTag.MatchesTagExact(FDuskyGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	// if input IS LMB and we ARE Targeting - Do yo thang, fire that bitch.
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}	
	}
	else
	{
		// Counting amount of time input has been held
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UDuskyAbilitySystemComponent* ADuskyPlayerController::GetASC()
{
	// If we haven't yet obtained the ASC 
	if (DuskyAbilitySystemComponent == nullptr)
	{
		// Do so now...
		DuskyAbilitySystemComponent = Cast<UDuskyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return DuskyAbilitySystemComponent;
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

	// Obtain DuskyInputComponent
	UDuskyInputComponent* DuskyInputComponent = CastChecked<UDuskyInputComponent>(InputComponent);

	// Bind the Move function to the Move Input Action
	DuskyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADuskyPlayerController::Move);
	// Bind Input Functions to Input Actions
	DuskyInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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

