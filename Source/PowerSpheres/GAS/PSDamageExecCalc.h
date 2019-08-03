// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PSUnitAttributeSet.h"
#include "PSDamageExecCalc.generated.h"

USTRUCT()
struct POWERSPHERES_API FAttrCaptureDef
{
	GENERATED_USTRUCT_BODY()

	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence);

	FAttrCaptureDef()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPSUnitAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPSUnitAttributeSet, Attack, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPSUnitAttributeSet, Defence, Target, false);
	}
};

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSDamageExecCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_UCLASS_BODY()

public:

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
	
};
