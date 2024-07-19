// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/EnemyClassInfo.h"
#include "Character/DuskyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "DuskyEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ADuskyAIController;

/**
 * 
 */
UCLASS()
class AURA_API ADuskyEnemy : public ADuskyCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ADuskyEnemy();
	virtual void PossessedBy(AController* NewController) override;

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHightlightActor() override;	// TODO: Fix this typo in all locations it appears.
	// Enemy Interface

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	// Combat Interface

	// Attribute Delegates for HealthBar Updates
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	// HitReact Goodies
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	EEnemyClass EnemyClass = EEnemyClass::Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ADuskyAIController> DuskyAIController;
};


