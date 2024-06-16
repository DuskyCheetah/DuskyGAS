// Copyright DuskyDev!


#include "DuskyCharacterBase.h"

// Sets default values
ADuskyCharacterBase::ADuskyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADuskyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADuskyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADuskyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

