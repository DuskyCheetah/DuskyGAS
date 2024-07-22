// Copyright DuskyDev!


#include "Loot/DuskyGear.h"

ADuskyGear::ADuskyGear()
{
}

ADuskyGear::ADuskyGear(const EItemRarity Rarity, const int ItemLevel, const EItemType ItemType)
{
	this->Rarity = Rarity;
	this->ItemLevel = ItemLevel;
	this->ItemType = ItemType;

	switch (this->Rarity)
	{
	case Normal:
		{
			//
			break;
		}
	case Magical:
		{
			//
			break;
		}
	case Rare:
		{
			//
			break;
		}
	case Legendary:
		{
			//
			break;
		}
	case Unique:
		{
			//
			break;
		}	
	}
}
