// Copyright DuskyDev!


#include "DuskyAssetManager.h"
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
}
