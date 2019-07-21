// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PSTypes.h"
#include "PSPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API APSPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ETeamType Team;
	
};
