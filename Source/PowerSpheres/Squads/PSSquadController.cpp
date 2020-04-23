// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSSquadController.h"

void APSSquadController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
