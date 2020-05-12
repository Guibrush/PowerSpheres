// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PSSquadController.generated.h"

/**
 *
 */
UCLASS()
class POWERSPHERES_API APSSquadController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;

protected:

	//Begin AController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//End AController Interface

};
