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

void APSPowerSphereCrateSpawnerManager::StartSpawning() const
{
	for (const APSPowerSphereCrateSpawner* Spawner : CrateSpawners)
	{
		if (CurrentCrates >= MaxCrates) { break; }
		if (!Spawner) { continue; }
		Spawner->TryToSpawnCrate();
	}
}
