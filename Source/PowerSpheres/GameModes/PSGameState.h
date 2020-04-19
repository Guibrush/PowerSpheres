// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Player/PSPlayerController.h"
#include "PSGameState.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API APSGameState : public AGameState
{
	GENERATED_BODY()

public:

	APSGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
