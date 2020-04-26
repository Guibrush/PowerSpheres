// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSPowerSphereCrateSpawner.generated.h"

UCLASS()
class POWERSPHERES_API APSPowerSphereCrateSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSPowerSphereCrateSpawner();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerSphereCrate")
	void TryToSpawnCrate() const;

};
