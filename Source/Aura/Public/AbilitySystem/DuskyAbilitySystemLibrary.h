// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/EnemyClassInfo.h"
#include "DuskyAbilitySystemLibrary.generated.h"


class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UDuskyAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "DuskyAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "DuskyAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "DuskyAbilitySystemLibrary|EnemyClassDefaults")
	static void InitializeEnemyDefaultAttributes(const UObject* WorldContextObject, EEnemyClass EnemyClass, float Level, UAbilitySystemComponent* ASC);

	// TODO: confirm if we initialize player class attributes here or elsewhere.
	//		 find out where it's currently initialized at the moment.
};
