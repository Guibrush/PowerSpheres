// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PSUnitAttributeSet.h"
#include "PSDamageExecCalc.generated.h"

USTRUCT()
struct POWERSPHERES_API FAttrDamageCaptureDef
{
	GENERATED_USTRUCT_BODY()

	// The DECLARE_ATTRIBUTE_CAPTUREDEF macro actually only declares two variables. The variable names are dependent on the input, however.
	// Here they will be HealthProperty(which is a UPROPERTY pointer) and HealthDef(which is a FGameplayEffectAttributeCaptureDefinition).
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence);

	FAttrDamageCaptureDef()
	{
		// We define the values of the variables we declared now. In this example, HealthProperty will point to the Health attribute in the 
		// UMyAttributeSet on the receiving target of this execution. The last parameter is a bool, and determines if we snapshot the 
		// attribute's value at the time of definition.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPSUnitAttributeSet, Health, Target, false);
		// This here is a different example: we still take the attribute from UMyAttributeSet, but this time it is Attack, 
		// and we look at the effect's source for it. We also want to snapshot is because the effect's strength should be determined during 
		// its initial creation. An attack wouldn't change damage values depending on the source's stat changes halfway through, after all.
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

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
