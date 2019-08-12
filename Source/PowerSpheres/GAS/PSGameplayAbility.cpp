// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSGameplayAbility.h"
#include "Units/PSUnit.h"
#include "Units/PSUnitController.h"

void UPSGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	UnitOwner = Cast<APSUnit>(ActorInfo->AvatarActor.Get());
	ControllerOwner = Cast<APSUnitController>(UnitOwner->GetController());
}

void UPSGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPSGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (bCancelItself)
	{
		if (UnitOwner && UnitOwner->CurrentAbilityType != EAbilityType::None)
		{
			TSubclassOf<class UPSGameplayAbility> CurrentAbility = UnitOwner->GetCurrentAbility();
			if (CurrentAbility == GetClass())
			{
				UnitOwner->CurrentAbilityType = EAbilityType::None;
				UnitOwner->CurrentAbilityParams = FAbilityParams();
			}
		}
	}
}
