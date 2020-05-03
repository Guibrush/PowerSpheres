// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSTypes.h"
#include "PSPowerSphere.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class POWERSPHERES_API UPSPowerSphere : public UObject
{
	GENERATED_BODY()

public:

	/** Type of ability. None indicates that this power sphere is an effect. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	EAbilityType AbilityType = EAbilityType::None;

	/** Gameplay effect that is going to be applied to the units equipped with this power sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	TSubclassOf<class UGameplayEffect> GameplayEffect;

	/** Ability that is going to be equipped to the units equipped with this power sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	TSubclassOf<class UPSGameplayAbility> GameplayAbility;

};
