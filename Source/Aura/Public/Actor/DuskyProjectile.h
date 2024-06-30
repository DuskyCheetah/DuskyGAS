// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DuskyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURA_API ADuskyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADuskyProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Result);
private:
	// Collision Sphere for Projectile
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
