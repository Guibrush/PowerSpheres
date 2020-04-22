// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSPowerSphereCrateSpawnerManager.generated.h"

class APSPowerSphereCrateSpawner;

UCLASS()
class POWERSPHERES_API UPSPowerSphereCrateSpawnerManager : public UObject
{
	GENERATED_BODY()
	// TODO: This shall be SINGLETON

private:
	UPROPERTY()
	TArray<APSPowerSphereCrateSpawner*> CrateSpawners;

public:
	TArray<APSPowerSphereCrateSpawner*> GetCrateSpawners() const { return CrateSpawners; }
};
