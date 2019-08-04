// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSDamageExecCalc.h"
#include "AbilitySystemComponent.h"
#include "Units/PSUnit.h"

UPSDamageExecCalc::UPSDamageExecCalc(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FAttrDamageCaptureDef Attributes;

	//RelevantAttributesToCapture is the array that contains all attributes you wish to capture, without exceptions.
	RelevantAttributesToCapture.Add(Attributes.HealthDef);
	RelevantAttributesToCapture.Add(Attributes.AttackDef);
	RelevantAttributesToCapture.Add(Attributes.DefenceDef);

	// An attribute added here on top of being added in RelevantAttributesToCapture will still be captured, 
	// but will not be shown for potential in-function modifiers in the GameplayEffect blueprint.
	InvalidScopedModifierAttributes.Add(Attributes.HealthDef);
}

void UPSDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Grab the ability system components.
	//UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	//UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	// Grab the actors.
	//AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	//AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	// Spec is the spec this execution originated from (the gameplay effect).
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	//We use the actor tags to set up an FAggregatorEvaluateParameters struct, which we will need to get the values of our captured attributes later.
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//Creating the attribute struct, we will need its values later when we want to get the attribute values.
	FAttrDamageCaptureDef Attributes;
	//float Health = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.HealthDef, EvaluationParameters, Health);
	float Attack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.AttackDef, EvaluationParameters, Attack);
	float Defence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.DefenceDef, EvaluationParameters, Defence);

	//Finally, we go through our simple example damage calculation. Attack comes from the Source actor and Defence comes from the Target actor.
	float DamageDone = FMath::Max<float>(Attack - Defence, 0.0f);

	// We allow to deal zero damage.
	if (DamageDone >= 0.f)
	{
		// We add an outgoing execution modifier to the Health attribute we got from our target, which is a modifier that can still be thrown out 
		// by the attribute system if it wishes to throw out the GameplayEffectExecutionCalculation.
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Attributes.HealthDef.AttributeToCapture, EGameplayModOp::Additive, -DamageDone));
	}
}
