// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DuskyInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FDuskyInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UDuskyInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	// Return InputAction associated with a given GameplayTag
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDuskyInputAction> AbilityInputActions;
};
