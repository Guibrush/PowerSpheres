// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PSTypes.h"
#include "Player/PSPlayerController.h"

#include "PSGameMode.generated.h"

class UPSPowerSphereCrateSpawnerManager;

UCLASS()
class POWERSPHERES_API APSGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	APSGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin AGameModeBase Interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;
	//virtual void PostLogin(APlayerController* NewPlayer) override;
	//virtual void HandleSeamlessTravelPlayer(AController*& C) override;
	virtual void RestartPlayer(AController* NewPlayer) override;
	virtual void HandleMatchHasStarted() override;
	virtual void StartPlay() override;
	//~ End AGameModeBase Interface

#if WITH_EDITOR
	/** Enemy Squads blueprints that are going to be spawned on PIE. WARNING: ONLY FOR TESTING PURPOSES. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APSSquad>> EnemySquadsToPIE;
#endif

private:
#if WITH_EDITOR
	ETeamType CurrentTeam;
#endif
	void AssignPlayerTeam(AController* Controller);
	void SpawnPlayerArmy(AController* Controller);

	// TODO: create exposed reference TSubclassOf<UPSPowerSphereCrateSpawnerManager>
	TWeakObjectPtr<UPSPowerSphereCrateSpawnerManager> PowerSphereCrateSpawnerManager;

};
