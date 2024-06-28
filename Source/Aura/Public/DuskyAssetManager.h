// Copyright DuskyDev!

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DuskyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDuskyAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UDuskyAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
