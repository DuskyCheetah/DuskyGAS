// Copyright DuskyDev!


#include "AbilitySystem/DuskyAbilitySystemLibrary.h"

#include "DuskyAbilityTypes.h"
#include "Game/DuslyGameModeBase.h"
#include "Interaction/CombatInterface.h"
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
	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetCharacterClassDefaultInfo(CharacterClass);

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

void UDuskyAbilitySystemLibrary::GivePlayerStartupAbilities(const UObject* WorldContextObject,
	UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	// Obtain GameMode - return if null because no crashie.
	ADuslyGameModeBase* DuskyGameMode = Cast<ADuslyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DuskyGameMode == nullptr) return;

	// Obtain CharacterClassInfo (Player)
	UCharacterClassInfo* ClassInfo = DuskyGameMode->CharacterClassInfo;
	// Crash prevention check
	if (ClassInfo == nullptr) return;

	// Non-Scaling abilities such as Death, Hit React & so on
	for (TSubclassOf<UGameplayAbility> AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec CommonAbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(CommonAbilitySpec);
	}

	// Start-up abilities - these will scale with level
	const FCharacterClassDefaultInfo& DefaultInfo = ClassInfo->GetCharacterClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility>AbilityClass : DefaultInfo.StartupAbilities)
	{
		// Obtain AvatarActor - Cast to CombatInterface
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		// If cast is successful
		if (CombatInterface)
		{
			// Create Ability Spec and instantiate with current player level
			FGameplayAbilitySpec StartupAbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			// Give Startup Abilities
			ASC->GiveAbility(StartupAbilitySpec);
		}
	}
}

void UDuskyAbilitySystemLibrary::GiveEnemyStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, EEnemyClass EnemyClass)
{
	// Obtain GameMode - return if null because no crashie.
	ADuslyGameModeBase* DuskyGameMode = Cast<ADuslyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (DuskyGameMode == nullptr) return;

	// Obtain EnemyClassInfo
	UEnemyClassInfo* ClassInfo = DuskyGameMode->EnemyClassInfo;
	// Crash prevention check
	if (ClassInfo == nullptr) return;

	// Non-Scaling abilities such as Death, Hit React & so on
	for (TSubclassOf<UGameplayAbility> AbilityClass : ClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec CommonAbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(CommonAbilitySpec);
	}

	// Start-up abilities - these will scale with level
	const FEnemyClassDefaultInfo& DefaultInfo = ClassInfo->GetEnemyClassDefaultInfo(EnemyClass);
	for (TSubclassOf<UGameplayAbility>AbilityClass : DefaultInfo.StartupAbilities)
	{
		// Obtain AvatarActor - Cast to CombatInterface
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		// If cast is successful
		if (CombatInterface)
		{
			// Create Ability Spec and instantiate with current (enemy) player level
			FGameplayAbilitySpec StartupAbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			// Give Startup Abilities
			ASC->GiveAbility(StartupAbilitySpec);
		}
	}
}

bool UDuskyAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<const FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return DuskyEffectContext->IsBlockedHit();
	}
	return false;
}

bool UDuskyAbilitySystemLibrary::IsDodgedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<const FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return DuskyEffectContext->IsDodgedHit();
	}
	return false;
}

bool UDuskyAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<const FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return DuskyEffectContext->IsCriticalHit();
	}
	return false;
}

void UDuskyAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsBlockedHit)
{
	if (FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DuskyEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UDuskyAbilitySystemLibrary::SetIsDodgedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsDodgedHit)
{
	if (FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DuskyEffectContext->SetIsDodgedHit(bInIsDodgedHit);
	}
}

void UDuskyAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FDuskyGameplayEffectContext* DuskyEffectContext = static_cast<FDuskyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		DuskyEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UDuskyAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		// Loop through each overlap result
		for (FOverlapResult& Overlap : Overlaps)
		{
			// Check actor implements CombatInterface, if and only if they do, then check if actor is alive
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				// Add actor to array - ensuring no duplicates
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
	}
}

bool UDuskyAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bAreFriendly = bBothArePlayers || bBothAreEnemies;

	return !bAreFriendly;
	
}
