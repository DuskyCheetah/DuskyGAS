// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemLibrary.h"

#include "Game/DuslyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/DuskyWidgetController.h"
#include "Player/DuskyPlayerState.h"
#include "UI/HUD/DuskyHUD.h"

UOverlayWidgetController* UDuskyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	// Obtain PlayerController - Must use WorldContextObject
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// Obtain DuskyHUD - if PC != Null
		if (ADuskyHUD* DuskyHUD = Cast<ADuskyHUD>(PC->GetHUD()))
		{
			// Obtain PlayerState
			ADuskyPlayerState* PS = PC->GetPlayerState<ADuskyPlayerState>();
			// Obtain ASC
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			// Obtain AS
			UAttributeSet* AS = PS->GetAttributeSet();

			// Create FWidgetControllerParams Struct
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			return DuskyHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UDuskyAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	// Obtain PlayerController - Must use WorldContextObject
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// Obtain DuskyHUD - if PC != Null
		if (ADuskyHUD* DuskyHUD = Cast<ADuskyHUD>(PC->GetHUD()))
		{
			// Obtain PlayerState
			ADuskyPlayerState* PS = PC->GetPlayerState<ADuskyPlayerState>();
			// Obtain ASC
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			// Obtain AS
			UAttributeSet* AS = PS->GetAttributeSet();

			// Create FWidgetControllerParams Struct
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			
			return DuskyHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UDuskyAbilitySystemLibrary::InitializeEnemyDefaultAttributes(const UObject* WorldContextObject, EEnemyClass EnemyClass, float Level, UAbilitySystemComponent* ASC)
{
	// Obtain GameMode - return if null because no crashie.
	ADuslyGameModeBase* DuskyGameMode = Cast<ADuslyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DuskyGameMode == nullptr) return;

	// Obtain Source for GE's (if needed)
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	// Obtain EnemyClassInfo
	UEnemyClassInfo* ClassInfo = DuskyGameMode->EnemyClassInfo;
	// Obtain ClassInfo for EnemyType
	FEnemyClassDefaultInfo ClassDefaultInfo = ClassInfo->GetEnemyClassDefaultInfo(EnemyClass);

	/*		Init Core Attributes		*/
	
	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle EnemyAttributesContextHandle = ASC->MakeEffectContext();
	EnemyAttributesContextHandle.AddSourceObject(AvatarActor);
	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle EnemyAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.EnemyAttributes, Level, EnemyAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*EnemyAttributesSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle

	/*		Init Derived Attributes		*/

	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle DerivedAttributesContextHandle = ASC->MakeEffectContext();
	DerivedAttributesContextHandle.AddSourceObject(AvatarActor);
	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle DerivedAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.DerivedAttributes, Level, DerivedAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*DerivedAttributeSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle

	/*		Init Vital Attributes		*/

	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle
}

void UDuskyAbilitySystemLibrary::InitializePlayerDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	// Obtain GameMode - return if null because no crashie.
	ADuslyGameModeBase* DuskyGameMode = Cast<ADuslyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DuskyGameMode == nullptr) return;

	// Obtain Source for GE's (if needed)
	AActor* AvatarActor = ASC->GetAvatarActor();

	// Obtain CharacterClassInfo
	UCharacterClassInfo* ClassInfo = DuskyGameMode->CharacterClassInfo;
	// Obtain ClassInfo for CharacterType
	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	/*		Init Core Attributes		*/
	
	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle CoreAttributesContextHandle = ASC->MakeEffectContext();
	CoreAttributesContextHandle.AddSourceObject(AvatarActor);

	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle CoreAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.CoreAttributes, Level, CoreAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*CoreAttributeSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle
	
	/*		Init Derived Attributes		*/

	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle DerivedAttributesContextHandle = ASC->MakeEffectContext();
	DerivedAttributesContextHandle.AddSourceObject(AvatarActor);

	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle DerivedAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.DerivedAttributes, Level, DerivedAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*DerivedAttributeSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle

	/*		Init Vital Attributes		*/

	// Create ContextHandle & Add SourceObject (in case it's needed)
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);

	// Create GESpecHandle to pass into ApplyGESpecToSelf
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());	// Must dereference the handle & .Data.Get() to retrieve the Spec from Handle
}
