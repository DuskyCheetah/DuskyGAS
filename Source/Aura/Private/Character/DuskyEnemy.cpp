// Copyright DuskyDev!


#include "Character/DuskyEnemy.h"
#include "AbilitySystem/DuskyAbilitySystemComponent.h"
#include "AbilitySystem/DuskyAbilitySystemLibrary.h"
#include "AbilitySystem/DuskyAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/DuskyUserWidget.h"
#include "DuskyGameplayTags.h"
#include "AI/DuskyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADuskyEnemy::ADuskyEnemy()
{
	// Change mesh default collision setting for visibility to Block
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDuskyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Disabling these features, as the rotation within Character Movement Comp is much smoother.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// This is the smooth one.
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UDuskyAttributeSet>("AttrbuteSet");	// TODO: Fix this typo in all locations.

	// Create HealthBar widget & Set attachment to root component.
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ADuskyEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// AI only matters on the server, so ensure we have authority.
	if (!HasAuthority()) return;

	// Initialize Controller, Blackboard, and BehaviorTree
	DuskyAIController = Cast<ADuskyAIController>(NewController);
	DuskyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	DuskyAIController->RunBehaviorTree(BehaviorTree);
	// Set Blackboard key values 
	DuskyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	DuskyAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedMob"), bIsRangedMob);
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
	// Set Blackboard key value
	if (DuskyAIController) DuskyAIController->GetBlackboardComponent()->SetValueAsBool(FName("isDead"), true);
	
	Super::Die();
}

void ADuskyEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ADuskyEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ADuskyEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;	// Set walk speed = to member varaible
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UDuskyAbilitySystemLibrary::GiveEnemyStartupAbilities(this, AbilitySystemComponent, EnemyClass);	// Grant enemy CommonAbilities
	}

	
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
	// Set blackboard key bool each time the value changes
	if (DuskyAIController && DuskyAIController->GetBlackboardComponent())
	{
		DuskyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
	
}

void ADuskyEnemy::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDuskyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	
}

void ADuskyEnemy::InitializeDefaultAttributes() const
{
	UDuskyAbilitySystemLibrary::InitializeEnemyDefaultAttributes(GetWorld(), EnemyClass, Level, AbilitySystemComponent);
}
