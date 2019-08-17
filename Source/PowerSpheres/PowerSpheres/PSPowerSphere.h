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

	/** Type of power sphere. This normally indicates if its a movement or an attack sphere, for example. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	EPowerSphereType PowerSphereType = EPowerSphereType::Generic;

	/** Gameplay effect that is going to be applied to the units equipped with this power sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	TSubclassOf<class UGameplayEffect> GameplayEffect;

	/** Ability that is going to be equipped to the units equipped with this power sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PowerSphereConfig)
	TSubclassOf<class UPSGameplayAbility> GameplayAbility;

};
