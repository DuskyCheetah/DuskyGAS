// Copyright DuskyDev!


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/DuskyAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// Capture Intelligence Attribute Value
	IntelligenceDef.AttributeToCapture = UDuskyAttributeSet::GetIntelligenceAttribute();
	// Capture Source of Attribute
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// Set Snapshot boolean
	IntelligenceDef.bSnapshot = false;

	// Add IntelligenceDef to MMC Array of Attributes to Capture
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Create the FAggregatorEvalParams & Set previously obtained Source/Target Tags
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Local Intelligence variable to store magnitude result
	float Intelligence = 0.f;
	// Capture Magnitude Result
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	// Prevent Intelligence from being less than 0. If so 0 set to 0.
	Intelligence = FMath::Max<float>(Intelligence , 0.f);

	// Obtain CombatInterface in order to GET PlayerLevel
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	// I personally prefer having my formulas outside the return statement
	float MaxManaMath = 50.f + (10.f * Intelligence) + (10.f * PlayerLevel);
	
	return MaxManaMath;
}
