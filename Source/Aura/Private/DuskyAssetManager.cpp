// Copyright DuskyDev!


#include "DuskyAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "DuskyGameplayTags.h"

UDuskyAssetManager& UDuskyAssetManager::Get()
{
	check(GEngine);
	UDuskyAssetManager* DuskyAssetManager = Cast<UDuskyAssetManager>(GEngine->AssetManager);
	return *DuskyAssetManager;
}

void UDuskyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FDuskyGameplayTags::InitializeNativeGameplayTags();

	/*	MUST CALL THIS FUNCTION IN ORDER TO UTILIZE TARGETDATA	*/
	UAbilitySystemGlobals::Get().InitGlobalData();
}
