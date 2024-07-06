// Copyright DuskyDev!


#include "AbilitySystem/Data/EnemyClassInfo.h"

FEnemyClassDefaultInfo UEnemyClassInfo::GetEnemyClassDefaultInfo(EEnemyClass EnemyClass)
{
	return EnemyClassInformation.FindChecked(EnemyClass);
}
