// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSSquadMemberComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPSSquadMemberComponent::UPSSquadMemberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;
}


// Called when the game starts
void UPSSquadMemberComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPSSquadMemberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
