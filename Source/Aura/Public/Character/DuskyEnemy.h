// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Character/DuskyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "DuskyEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class AURA_API ADuskyEnemy : public ADuskyCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ADuskyEnemy();

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHightlightActor() override;	// TODO: Fix this typo in all locations it appears.
	// Enemy Interface

	// Combat Interface
	virtual int32 GetPlayerLevel() override;
	// Combat Interface

	// Attribute Delegates for HealthBar Updates
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
};


