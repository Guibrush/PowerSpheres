// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSUnitAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Units/PSUnit.h"
#include "GameplayEffectExtension.h"

void UPSUnitAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPSUnitAttributeSet, Health);
	DOREPLIFETIME(UPSUnitAttributeSet, MaxHealth);
	DOREPLIFETIME(UPSUnitAttributeSet, Movement);
	DOREPLIFETIME(UPSUnitAttributeSet, Attack);
	DOREPLIFETIME(UPSUnitAttributeSet, Defence);
	DOREPLIFETIME(UPSUnitAttributeSet, ElementalDefence);
}

FGameplayAttribute UPSUnitAttributeSet::GetHealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Health));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetMaxHealthAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, MaxHealth));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetMovementAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Movement));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetAttackAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Attack));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetDefenceAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Defence));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetElementalDefenceAttribute()
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, ElementalDefence));
	return FGameplayAttribute(Property);
}

void UPSUnitAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	UAbilitySystemComponent* Source = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();

	if (GetHealthAttribute() == Data.EvaluatedData.Attribute)
	{
		// Get the Target actor
		AActor* DamagedActor = nullptr;
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		}

		// Get the Source actor
		AActor* AttackingActor = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			AttackingActor = Source->AbilityActorInfo->AvatarActor.Get();
		}

		// Clamp health
		float FinalHealth = FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetBaseValue());
		Health.SetBaseValue(FinalHealth);
		Health.SetCurrentValue(FinalHealth);
		if (FinalHealth <= 0)
		{
			// Handle death.
			APSUnit* DamagedUnit = Cast<APSUnit>(DamagedActor);
			APSUnit* AttackingUnit = Cast<APSUnit>(AttackingActor);
			if (DamagedUnit && AttackingUnit)
			{
				// Construct a gameplay cue event for this death
				//FGameplayCueParameters Params(Data.EffectSpec.GetContext());
				//Params.RawMagnitude = Data.EvaluatedData.Magnitude;;
				//Params.NormalizedMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude / MaxHealth);
				//Params.AggregatedSourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
				//Params.AggregatedTargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

				//GASChar->Die(DamagedController, DamagedActor, Data.EffectSpec, Params.RawMagnitude, Params.Normal);

				DamagedUnit->Die(AttackingUnit);
				AttackingUnit->TargetDied(DamagedUnit);
			}
		}
	}
}
