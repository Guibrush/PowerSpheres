// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSPowerSphereCrate.h"

// Sets default values
APSPowerSphereCrate::APSPowerSphereCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APSPowerSphereCrate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APSPowerSphereCrate, IsOpened);
}

bool APSPowerSphereCrate::TryToOpen_Implementation()
{
	// Implemented in BP
	return false;
}

