// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSPowerSphereCrateSpawnerManager.generated.h"

class APSPowerSphereCrateSpawner;

// TODO: This shall be SINGLETON
UCLASS()
class POWERSPHERES_API APSPowerSphereCrateSpawnerManager : public AActor
{
	GENERATED_BODY()

private:
	
	TArray<const APSPowerSphereCrateSpawner*> CrateSpawners;

public:
	
	APSPowerSphereCrateSpawnerManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerSphereCrate")
	int32 MaxCrates = 0;

	UPROPERTY(BlueprintReadWrite, Category = "PowerSphereCrate")
	int32 CurrentCrates = 0;

	TArray<const APSPowerSphereCrateSpawner*> GetCrateSpawners() const { return CrateSpawners; }

	UFUNCTION(BlueprintCallable, Category = "PowerSphereCrate")
	void RegisterCrateSpawner(const APSPowerSphereCrateSpawner* CrateSpawner);

	void StartSpawning();

};
