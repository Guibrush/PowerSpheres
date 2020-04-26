// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSPowerSphereCrateSpawnerManager.h"

APSPowerSphereCrateSpawnerManager::APSPowerSphereCrateSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APSPowerSphereCrateSpawnerManager::RegisterCrateSpawner(const APSPowerSphereCrateSpawner* Spawner)
{
	CrateSpawners.AddUnique(Spawner);
}

void APSPowerSphereCrateSpawnerManager::StartSpawning()
{	
	// Shuffle CrateSpawners, Fisher–Yates algorithm
	for (int32 i = CrateSpawners.Num() - 1; i != 0; i--) {
		int32 j = FMath::RandRange(0, i);
		CrateSpawners.Swap(i, j);
	}

	for (const APSPowerSphereCrateSpawner* Spawner : CrateSpawners)
	{
		if (CurrentCrates >= MaxCrates) { break; }
		if (!Spawner) { continue; }
		Spawner->TryToSpawnCrate();
	}
}
