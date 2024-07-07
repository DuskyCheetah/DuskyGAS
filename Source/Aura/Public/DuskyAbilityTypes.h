// Copyright DuskyDev!

#pragma once

#include "GameplayEffectTypes.h"
#include "DuskyAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDuskyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:	// redundant, but bear with me

	// Getters for hit metrics
	bool IsBlockedHit() const { return bIsBlockedHit; }
	bool IsDodgedHit() const { return bIsDodgedHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; } 

	// Setters for hit metrics
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsDodgedHit(bool bInIsDodgedHit) { bIsDodgedHit = bInIsDodgedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	
	// Returns the actual struct used for serialization, subclasses must override this!
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsDodgedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
	
};