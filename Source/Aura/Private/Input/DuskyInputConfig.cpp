// Copyright DuskyDev!


#include "Input/DuskyInputConfig.h"

const UInputAction* UDuskyInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// Iterate through Custom InputAction Struct
	for (const FDuskyInputAction& Action : AbilityInputActions )
	{
		// If InputAction != null && It's tag matches the passed in tag
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}	
