// Copyright DuskyDev!


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/DuskyAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// Capture Vitality Attribute Value
	VitalityDef.AttributeToCapture = UDuskyAttributeSet::GetVitalityAttribute();
	// Capture Source of Attribute
	VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// Set Snapshot boolean
	VitalityDef.bSnapshot = false;

	// Add VitalityDef to MMC Array of Attributes to Capture
	RelevantAttributesToCapture.Add(VitalityDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Create the FAggregatorEvalParams & Set previously obtained Source/Target Tags
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Local Vitality variable to store Magnitude result.
	float Vitality = 0.f;
	// Capture Magnitude result
	GetCapturedAttributeMagnitude(VitalityDef, Spec, EvaluationParameters, Vitality);
	// Prevent Vitality from being less than 0. If so - set to 0.
	Vitality = FMath::Max<float>(Vitality, 0.f);

	// Obtain CombatInterface in order to GET PlayerLevel
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	float MaxHealthMath = 80.f + (10.f * Vitality) + (10.f * PlayerLevel);
	return MaxHealthMath;
}
