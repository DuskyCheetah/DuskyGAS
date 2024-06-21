// Copyright DuskyDev!


#include "Actor/DuskyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "Components/SphereComponent.h"

ADuskyEffectActor::ADuskyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void ADuskyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	// Using const_cast is a huge NO NO. 
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// Should the actor who overlapped, implement an AbilitySystemComponent
		// Locally store a reference to it's AttributeSet
		const UDuskyAttributeSet* DuskyAttributeSet = Cast<UDuskyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UDuskyAttributeSet::StaticClass()));

		// THIS IS THE HUGE NO NO. DONT DO THIS
		UDuskyAttributeSet* MutableDuskyAttributeSet = const_cast<UDuskyAttributeSet*>(DuskyAttributeSet);
		MutableDuskyAttributeSet->SetHealth(DuskyAttributeSet->GetHealth() + 25.f);
		// THIS IS THE HUGE NO NO. DONT DO THIS

		Destroy();
	}
}

void ADuskyEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ADuskyEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADuskyEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADuskyEffectActor::EndOverlap);
}


