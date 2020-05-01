// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSUnitAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Units/PSUnit.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MapRevealerComponent.h"

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

FGameplayAttribute UPSUnitAttributeSet::GetHealthAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Health));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetMaxHealthAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, MaxHealth));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetMovementAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Movement));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetAttackAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Attack));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetDefenceAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, Defence));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetElementalDefenceAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, ElementalDefence));
	return FGameplayAttribute(Property);
}

FGameplayAttribute UPSUnitAttributeSet::GetVisionRadiusAttribute() const
{
	static UProperty* Property = FindFieldChecked<UProperty>(UPSUnitAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UPSUnitAttributeSet, VisionRadius));
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

		APSUnit* DamagedUnit = Cast<APSUnit>(DamagedActor);
		APSUnit* AttackingUnit = Cast<APSUnit>(AttackingActor);
		if (DamagedUnit && AttackingUnit)
		{
			// Construct a gameplay cue event for this death
			FGameplayCueParameters Params(Data.EffectSpec.GetContext());
			Params.RawMagnitude = Data.EvaluatedData.Magnitude;
			Params.NormalizedMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude / MaxHealth.GetBaseValue());
			//Params.AggregatedSourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
			//Params.AggregatedTargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

			DamagedUnit->UnitDamaged(AttackingUnit, Params);

			// Handle death.
			if (FinalHealth <= 0)
			{
				DamagedUnit->Die(AttackingUnit);
				AttackingUnit->TargetDied(DamagedUnit);
			}
		}
	}
	else if (GetMovementAttribute() == Data.EvaluatedData.Attribute)
	{
		AActor* DamagedActor = nullptr;
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		}

		if (APSUnit* DamagedUnit = Cast<APSUnit>(DamagedActor))
		{
			float MovementSpeed = Movement.GetCurrentValue();
			DamagedUnit->GetCharacterMovement()->MaxWalkSpeed *= MovementSpeed;
			DamagedUnit->GetCharacterMovement()->MaxAcceleration *= MovementSpeed;
		}
	}
	else if (GetVisionRadiusAttribute() == Data.EvaluatedData.Attribute)
	{
		AActor* DamagedActor = nullptr;
		if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
		{
			DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		}

		if (APSUnit * DamagedUnit = Cast<APSUnit>(DamagedActor))
		{
			float NewVisionRadius = VisionRadius.GetCurrentValue();
			DamagedUnit->GetMapRevealer()->SetBoxExtent(FVector(NewVisionRadius, NewVisionRadius, 0.0f));
		}
	}
}
