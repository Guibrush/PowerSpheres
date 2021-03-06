// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "Units/PSUnitController.h"
#include "Units/PSUnit.h"
#include "Squads/PSSquadController.h"
#include "Squads/PSSquad.h"
#include "PSBTTask.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSBTTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:

	/** PSUnitController owner of this Decorator or null if the owner is not a PSUnitController. */
	UPROPERTY(BlueprintReadOnly)
	APSUnitController* UnitControllerOwner = nullptr;

	/** PSUnit owner of this Decorator or null if the owner is not a PSUnit. */
	UPROPERTY(BlueprintReadOnly)
	APSUnit* UnitOwner = nullptr;

	/** PSSquadController owner of this Decorator or null if the owner is not a PSSquadController. */
	UPROPERTY(BlueprintReadOnly)
	APSSquadController* SquadControllerOwner = nullptr;

	/** PSSquad owner of this Decorator or null if the owner is not a PSSquad. */
	UPROPERTY(BlueprintReadOnly)
	APSSquad* SquadOwner = nullptr;

	// Begin UBTNode interface
	virtual void SetOwner(AActor* ActorOwner) override;
	// End UBTNode interface
	
};
