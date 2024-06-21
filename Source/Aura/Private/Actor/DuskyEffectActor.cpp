// Copyright DuskyDev!


#include "Actor/DuskyEffectActor.h"
#include "Components/SphereComponent.h"

ADuskyEffectActor::ADuskyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	
}

void ADuskyEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}


