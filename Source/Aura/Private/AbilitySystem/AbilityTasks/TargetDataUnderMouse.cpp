// Copyright DuskyDev!


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	// Create new AbilityTask
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
		SendMouseCursorData();
	else
	{
		// Local Handle & PredKey for following actions.
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		
		// Upon calling Activate on server - Bind callback to delegate
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		// Checking if TargetDataDelegate has been Set
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		// If it hasn't - flag waiting for PlayerData.
		if (!bCalledDelegate)
			SetWaitingOnRemotePlayerData();
	}
	
	

}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	// Create ScopedPredictionWindow - allowing everything in this method to be predicted on the server.
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	// Obtain PlayerController
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	// Obtain hit result under cursor and store in CursorHit
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	// Create DataHandle to pass into SetReplicatedTargetData
	FGameplayAbilityTargetDataHandle DataHandle;
	// Create new object of Type FGameplayAbilityTargetData_SingleTargetHit
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	// Store HitResult in local CursorHit
	Data->HitResult = CursorHit;
	// Add Data to DataHandle for following method call
	DataHandle.Add(Data);

	// Send TargetData up to Server.
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	// Ensure ability is still active before broadcasting delegate
	if (ShouldBroadcastAbilityTaskDelegates())
		ValidData.Broadcast(DataHandle);
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	// TargetData received - Don't store it any further.
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	// Ensure ability is still active before broadcasting delegate
	if (ShouldBroadcastAbilityTaskDelegates())
		ValidData.Broadcast(DataHandle);
}
