// Copyright DuskyDev!

#pragma once

#include "GameplayEffectTypes.h"
#include "DuskyAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDuskyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
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

	// Creates a copy of this context, used to duplicate for later modifications
	virtual FDuskyGameplayEffectContext* Duplicate() const
	{
		FDuskyGameplayEffectContext* NewContext = new FDuskyGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}

		return NewContext;
	}

	// Custom serialization, subclasses must override this
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	
protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsDodgedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
	
};

// Defining StructOps for our custom FDuskyGameplayEffectContext, allowing us to Serialize into FArchive and make copies
template<>
struct TStructOpsTypeTraits<FDuskyGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FDuskyGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};