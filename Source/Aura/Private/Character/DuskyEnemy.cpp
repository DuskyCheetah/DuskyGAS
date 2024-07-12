// Copyright DuskyDev!


#include "Character/DuskyEnemy.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAbilitySystemLibrary.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/DuskyUserWidget.h"
#include "DuskyGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"


ADuskyEnemy::ADuskyEnemy()
{
	// Change mesh default collision setting for visibility to Block
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDuskyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UDuskyAttributeSet>("AttrbuteSet");	// TODO: Fix this typo in all locations.

	// Create HealthBar widget & Set attachment to root component.
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ADuskyEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ADuskyEnemy::UnHightlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ADuskyEnemy::GetPlayerLevel()
{
	return Level;
}

void ADuskyEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void ADuskyEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;	// Set walk speed = to member varaible
	InitAbilityActorInfo();
	UDuskyAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);	// Grant enemy CommonAbilities
	
	// Obtain DuskyUserWidget & Cast to HealthBar
	if (UDuskyUserWidget* DuskyUserWidget = Cast<UDuskyUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		// Set WidgetController to DuskyEnemy.
		DuskyUserWidget->SetWidgetController(this);
	}
	
	// Obtain DuskyAttributeSet
	if (const UDuskyAttributeSet* DuskyAS = Cast<UDuskyAttributeSet>(AttributeSet))
	{
		// Bind to OnHealthChanged Delegate via Lambda
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		// Bind to OnMaxHealthChanged Delegate via Lambda
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DuskyAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		// Anytime an enemy receives the HitReact Tag - HitReactTagChanged will be called in response
		AbilitySystemComponent->RegisterGameplayTagEvent(FDuskyGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
				this,
				&ADuskyEnemy::HitReactTagChanged
		);
		
		// Broadcast initial values of Health / Max Health
		OnHealthChanged.Broadcast(DuskyAS->GetHealth());
		OnMaxHealthChanged.Broadcast(DuskyAS->GetMaxHealth());
	}
}

void ADuskyEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	// Set HitReacting boolean
	bHitReacting = NewCount > 0;
	// MaxWalkSpeed = 0 whilst reacting - else = to BaseWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void ADuskyEnemy::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDuskyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ADuskyEnemy::InitializeDefaultAttributes() const
{
	UDuskyAbilitySystemLibrary::InitializeEnemyDefaultAttributes(GetWorld(), EnemyClass, Level, AbilitySystemComponent);
}
