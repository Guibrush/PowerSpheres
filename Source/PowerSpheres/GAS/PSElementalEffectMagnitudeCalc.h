// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "PSUnitAttributeSet.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PSElementalEffectMagnitudeCalc.generated.h"

USTRUCT()
struct POWERSPHERES_API FAttrElementalEffectCaptureDef
{
	GENERATED_USTRUCT_BODY()

	DECLARE_ATTRIBUTE_CAPTUREDEF(ElementalDefence);

	FAttrElementalEffectCaptureDef()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPSUnitAttributeSet, ElementalDefence, Target, false);
	}
};

/**
 *
 */
UCLASS()
class POWERSPHERES_API UPSElementalEffectMagnitudeCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_UCLASS_BODY()

public:

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
