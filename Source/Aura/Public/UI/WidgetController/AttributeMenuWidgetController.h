// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/DuskyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UDuskyAttributeInfo;
struct FAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDuskyAttributeInfoSignature, const FAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UDuskyWidgetController
{
	GENERATED_BODY()

public:

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FDuskyAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDuskyAttributeInfo> AttributeInfo;
};
