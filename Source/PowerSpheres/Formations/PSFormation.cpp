// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSFormation.h"

// Sets default values
APSFormation::APSFormation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APSFormation::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UPSFormationComponent>(FormationPositions);

	// Sort the array of scene component according to their distance to the (0, 0) of the actor.
	FormationPositions.Sort([](const UPSFormationComponent& ComponentA, const UPSFormationComponent& ComponentB)
		{
			float DistanceA = FVector::DistSquared(FVector::ZeroVector, ComponentA.GetRelativeLocation());
			float DistanceB = FVector::DistSquared(FVector::ZeroVector, ComponentB.GetRelativeLocation());
			return DistanceA < DistanceB;
		});
}

// Called every frame
void APSFormation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

