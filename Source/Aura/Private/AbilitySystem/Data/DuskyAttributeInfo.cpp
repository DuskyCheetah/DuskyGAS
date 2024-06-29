// Copyright DuskyDev!


#include "AbilitySystem/Data/DuskyAttributeInfo.h"

FAttributeInfo UDuskyAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag,
	bool bLogNotFound) const
{
	// Iterate through AttributeInformation
	for (const FAttributeInfo& Info : AttributeInformation)
	{
		// Try to match passed in Tag with Tag w/i array
		if (Info.AttributeTag == AttributeTag)
		{
			// Return said tag
			return Info;
		}
	}
	// IF we pass in bLogNotFound = True - Send an error
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	// Return empty FDuskyAttributeInfo if no match
	return FAttributeInfo();
}
