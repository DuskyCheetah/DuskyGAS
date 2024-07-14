// Copyright DuskyDev!


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "DuskyAbilityTypes.h"
#include "DuskyGameplayTags.h"
#include "AbilitySystem/DuskyAbilitySystemLibrary.h"
#include "AbilitySystem/DuskyAttributeSet.h"

// Not a USTRUCT - raw internal struct not exposed to Unreal systems.
struct DuskyDamageStatics
{
	// CaptureDef Creation Step 1 of 3:
	// Creating Attribute Capture Definitions for Stats needing to capture for damage calcs.
	// Target Attributes
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DodgeChance);

	// Source Attributes
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPen);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	
	DuskyDamageStatics()
	{
		// CaptureDef Creation Step 2 of 3:
		// Define the declared CaptureDef above ^^
		// Target Attributes
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, DodgeChance, Target, false);

		// Source Attributes
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, ArmorPen, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, CriticalHitDamage, Source, false);
	}
};

// Static variable that persists infinitely. Everytime it's called, the same DStatics is returned. 
static const DuskyDamageStatics& DamageStatics()
{
	static DuskyDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	// CaptureDef Creation Step 3 of 3:
	// Add created CaptureDefs to RelevantAttributesToCapture Array
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().DodgeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Create pointers for Source/Target AbilitySystemComponents
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	// Create pointers for Source/Target Avatar Actors.
	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	// Get owning Gameplay Effect Spec
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather tags from Source and Target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Create and populate EvaluationParams
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Obtain EffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// Get Damage Set by Caller Magnitude
	float LocalDamage = Spec.GetSetByCallerMagnitude(FDuskyGameplayTags::Get().Damage);

	
	// Capture BlockChance on Target, and determine if there was a successful block.
	float LocalBlock = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, LocalBlock);
	LocalBlock = FMath::Max<float>(LocalBlock, 0.f);	// Clamped Blocked Chance to prevent negative values
	
	// BlockChance roll to determine yay or nay on blocked hit.
	const bool bBlockedHit = FMath::RandRange(1, 100) < LocalBlock;
	// Set Blocked Result 
	UDuskyAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlockedHit);
	if (bBlockedHit) LocalDamage = 0;




	// Capture DodgeChance on Target and determine if they successfully dodged this hit.
	float LocalDodge = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DodgeChanceDef, EvaluationParameters, LocalDodge);
	LocalDodge = FMath::Max<float>(LocalDodge, 0.f);

	// DodgeChance roll to determine yay or nay on Dodged Hit
	const bool bDodgedHit = FMath::RandRange(1, 100) < LocalDodge;
	// Set Dodge Result
	UDuskyAbilitySystemLibrary::SetIsDodgedHit(EffectContextHandle, bDodgedHit);
	if (bDodgedHit) LocalDamage = 0;
	
	// If hit was Blocked or Dodged - We don't need to further calculate damage.
	if (!bBlockedHit && !bDodgedHit)
	{
		// Capture Armor from Target for Damage mitigation calculations
		float LocalTargetArmor = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, LocalTargetArmor);
		LocalTargetArmor = FMath::Max<float>(LocalTargetArmor, 0.f);

		// Capture Armor Penetration from Source for Damage Mitigation...Mitigation.
		float LocalSourceArmorPen = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenDef, EvaluationParameters, LocalSourceArmorPen);
		LocalSourceArmorPen = FMath::Max<float>(LocalSourceArmorPen, 0.f); // ArmorPen is a % based stat. Capping it at 100%.

		// Effective Target Armor value after Armor Pen considerations
		const float EffectiveTargetArmor = LocalTargetArmor * ( 100 - LocalSourceArmorPen ) / 100.f;
		
		// TODO: Work on how we want to calculate the mitigating effects of Armor to Damage.
		LocalDamage *= ( 100 - EffectiveTargetArmor ) / 100.f;
		// I think possibly adding an attribute to the attribute set derived attribute from a curve table,
		// altering the value based on character levels.

		// Capture CriticalHitChance from Source to determine if hit was critical.
		float LocalSourceCritHit = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, LocalSourceCritHit);
		LocalSourceCritHit = FMath::Max<float>(LocalSourceCritHit, 0.f);

		// Capture CriticalHitDamage from Source to further amplify damage done if hit was indeed Critical.
		float LocalSourceCritDamage = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, LocalSourceCritDamage);
		LocalSourceCritDamage = FMath::Max<float>(LocalSourceCritDamage, 0.f);

		// Roll for Critical Hit
		// Critical Hits deal double damage + CriticalHitDamage bonus.
		const bool bCriticalHit = FMath::RandRange(0 , 100) < LocalSourceCritHit;
		// Set Critical Hit Result
		UDuskyAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);
		if (bCriticalHit) LocalDamage = LocalDamage * 2 + (LocalDamage * (LocalSourceCritDamage / 100));
	
	}
	
	// Construct EvaluatedData, Obtain Damage Meta Attribute, Declare Modifer Operation, and involve our LocalDamage variable
	const FGameplayModifierEvaluatedData EvaluatedData(UDuskyAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, LocalDamage);
	// Pass the EvaluatedData into AddOutputMod to pass on LocalDamage modifications we made in this function.
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
