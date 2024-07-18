// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "DuskyPlayerController.generated.h"

class UFloatingTextComponent;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UDuskyInputConfig;
class UDuskyAbilitySystemComponent;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURA_API ADuskyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADuskyPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowFloatingNumber(float Value, ACharacter* TargetCharacter, bool bBlockedHit, bool bDodgedHit, bool bCriticalHit);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Project-wide Context file.
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DuskyContext;

	// Character Movement Action
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// Shift Input Action
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;
	void ShiftPressed() { bShiftKeyDown = true;}
	void ShiftReleased() { bShiftKeyDown = false;}
	bool bShiftKeyDown = false;
	
	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	// This special wrapper is needed for holding member interface pointers.
	// DO not use raw pointers.
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	
	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UDuskyInputConfig> InputConfig;

	// Local pointer to the ASC for user throughout the CPP file.
	UPROPERTY()
	TObjectPtr<UDuskyAbilitySystemComponent> DuskyAbilitySystemComponent;

	UDuskyAbilitySystemComponent* GetASC();

	// Store the destination of click
	FVector CachedDestination = FVector::ZeroVector;
	// Amount of time the movement key has been held
	float FollowTime = 0.f;
	// Setting the threshold for what a "Short Press Is"
	float ShortPressThreshold = 0.5f;
	// Boolean tracking whether we should be auto running a path.
	bool bAutoRunning = false;
	//
	bool bTargeting = false;
	// Customizable Auto Running Acceptance Radius
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	//
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFloatingTextComponent> FloatingTextComponentClass;
};
