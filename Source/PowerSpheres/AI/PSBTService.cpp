// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSBTService.h"

void UPSBTService::SetOwner(AActor* InActorOwner)
{
	Super::SetOwner(InActorOwner);

	UnitControllerOwner = Cast<APSUnitController>(AIOwner);
	if (UnitControllerOwner)
		UnitOwner = Cast<APSUnit>(UnitControllerOwner->GetPawn());

	SquadControllerOwner = Cast<APSSquadController>(AIOwner);
	if (SquadControllerOwner)
		SquadOwner = Cast<APSSquad>(SquadControllerOwner->GetPawn());
}
