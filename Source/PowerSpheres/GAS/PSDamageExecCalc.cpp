// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSDamageExecCalc.h"

UPSDamageExecCalc::UPSDamageExecCalc(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FAttrCaptureDef Attributes;

	RelevantAttributesToCapture.Add(Attributes.HealthDef);
	RelevantAttributesToCapture.Add(Attributes.AttackDef);
	RelevantAttributesToCapture.Add(Attributes.DefenceDef);

	InvalidScopedModifierAttributes.Add(Attributes.HealthDef);
}

void UPSDamageExecCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
}
