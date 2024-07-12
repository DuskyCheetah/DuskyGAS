// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFloatingTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFloatingText(float Value);
};
