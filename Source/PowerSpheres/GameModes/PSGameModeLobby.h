// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameMode.h"
#include "PSGameModeLobby.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API APSGameModeLobby : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APSGameMode> DefaultGameMode;

	/** Starts a game in the specified map with all the clients connected at the moment of the call. */
	UFUNCTION(BlueprintCallable, Category = PSGame)
	bool StartGame(const FString& MapName, const FString& Options, bool bSeamless);
	
};
