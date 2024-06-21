// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DuskyEffectActor.generated.h"

class USphereComponent;

UCLASS()
class AURA_API ADuskyEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADuskyEffectActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

};
