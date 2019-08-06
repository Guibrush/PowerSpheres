// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSElementalEffectMagnitudeCalc.h"

UPSElementalEffectMagnitudeCalc::UPSElementalEffectMagnitudeCalc(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FAttrElementalEffectCaptureDef Attributes;

	RelevantAttributesToCapture.Add(Attributes.ElementalDefenceDef);
}

float UPSElementalEffectMagnitudeCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	FAttrElementalEffectCaptureDef Attributes;
	float ElementalDefence = 0.f;
	GetCapturedAttributeMagnitude(Attributes.ElementalDefenceDef, Spec, EvaluationParameters, ElementalDefence);

	// We calculate only the percentaje of the elemental defence of the target because this value is going to be
	// multiplied by the coeffecient which is the base duration of the gameplay effect.
	float Percentaje = (1 - (ElementalDefence * 0.01));
	// We make sure that we at the very least return 0.1f because if we return zero the effect is going to be applied
	// infinitely.
	return FMath::Max<float>(Percentaje, 0.1f);
}
