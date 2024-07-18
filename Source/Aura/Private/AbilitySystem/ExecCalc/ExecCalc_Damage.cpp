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
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CausticResistance);

	// Source Attributes
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPen);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	DuskyDamageStatics()
	{
		// CaptureDef Creation Step 2 of 3:
		// Define the declared CaptureDef above ^^
		// Target Attributes
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, DodgeChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, FrostResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, CausticResistance, Target, false);

		// Source Attributes
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, ArmorPen, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDuskyAttributeSet, CriticalHitDamage, Source, false);

		// Map AttributeDefs to respective Attribute gameplay tag.
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Defensive_Armor, ArmorDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Defensive_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Defensive_DodgeChance, DodgeChanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Resistance_Frost, FrostResistanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Resistance_Caustic, CausticResistanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Offensive_ArmorPen, ArmorPenDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Offensive_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(FDuskyGameplayTags::Get().Attributes_Offensive_CriticalHitDamage, CriticalHitDamageDef);
		
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
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CausticResistanceDef);
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

	// Local Damage variable for processing
	float LocalDamage = 0.f;

	// Loop through all damage types and add value to damage - if damage type was found
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FDuskyGameplayTags::Get().DamageTypesToResists)
	{
		// Obtain DamageType and corresponding ResistanceTag from current element.
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		
		// Check if current ResistanceTag is found within Map - crash message just in case.
		//checkf(DuskyDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		//const FGameplayEffectAttributeCaptureDefinition CaptureDef = DuskyDamageStatics().TagsToCaptureDefs[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);
		
		float LocalResistance = 0.f;
		// Capture the resistance value in a local resistance variable.
		//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, LocalResistance);
		// Clamp Resistance attribute between 0% and 80%
		//LocalResistance = FMath::Clamp(LocalResistance, 0.f, 80.f);

		// Mitigate Damage value in regard to Resistance value.
		//DamageTypeValue *= ( 100.f - LocalResistance ) / 100.f;	// TODO: I do not want resistance to be a 1:1 ratio. Work out a formula.
		
		// DamageTypeValue returns 0 if not found - so this adds all relevant damage type values.
		LocalDamage += DamageTypeValue;
	}
	
	// Capture BlockChance on Target, and determine if there was a successful block.
	float LocalBlock = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, LocalBlock);
	LocalBlock = FMath::Max<float>(LocalBlock, 0.f);	// Clamped Blocked Chance to prevent negative values
	
	// BlockChance roll to determine yay or nay on blocked hit.
	const bool bBlockedHit = FMath::RandRange(1, 100) < LocalBlock;
	// Set Blocked Result 
	UDuskyAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlockedHit);
	if (bBlockedHit) LocalDamage = 0;

	
	// If hit was Blocked - We don't need to further calculate damage.
	if (!bBlockedHit)
	{

		// Capture DodgeChance on Target and determine if they successfully dodged this hit.
		float LocalDodge = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DodgeChanceDef, EvaluationParameters, LocalDodge);
		LocalDodge = FMath::Max<float>(LocalDodge, 0.f);

		// DodgeChance roll to determine yay or nay on Dodged Hit
		const bool bDodgedHit = FMath::RandRange(1, 100) < LocalDodge;
		// Set Dodge Result
		UDuskyAbilitySystemLibrary::SetIsDodgedHit(EffectContextHandle, bDodgedHit);
		if (bDodgedHit) LocalDamage = 0;

		// If hit was Dodged - No further calculations needed.
		if (!bDodgedHit)
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
	}
	
	// Construct EvaluatedData, Obtain Damage Meta Attribute, Declare Modifer Operation, and involve our LocalDamage variable
	const FGameplayModifierEvaluatedData EvaluatedData(UDuskyAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, LocalDamage);
	// Pass the EvaluatedData into AddOutputMod to pass on LocalDamage modifications we made in this function.
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
