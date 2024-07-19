// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DuskyAIController.generated.h"


class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class AURA_API ADuskyAIController : public AAIController
{
	GENERATED_BODY()

public:

	ADuskyAIController();

protected:
	
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
