// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#include "PSUnitController.h"
#include "Navigation/CrowdFollowingComponent.h"

APSUnitController::APSUnitController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

void APSUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
