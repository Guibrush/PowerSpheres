// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSUnitController.h"

void APSUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
