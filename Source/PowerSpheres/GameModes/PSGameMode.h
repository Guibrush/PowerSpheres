// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PSTypes.h"
#include "Player/PSPlayerController.h"
#include "PSGameMode.generated.h"

//USTRUCT()
//struct POWERSPHERES_API FPlayerControllersTeam
//{
//	GENERATED_USTRUCT_BODY()
//
//	FPlayerControllersTeam()
//		: Team(TArray<APSPlayerController*>())
//	{ }
//
//	UPROPERTY()
//	TArray<APSPlayerController*> Team;
//};

UCLASS()
class POWERSPHERES_API APSGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	APSGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//UPROPERTY()
	//TMap<ETeamType, FPlayerControllersTeam> Teams;

	//~ Begin AGameModeBase Interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;
	//virtual void PostLogin(APlayerController* NewPlayer) override;
	//virtual void HandleSeamlessTravelPlayer(AController*& C) override;
	virtual void RestartPlayer(AController* NewPlayer) override;
	//~ End AGameModeBase Interface

private:
#if WITH_EDITOR
	ETeamType CurrentTeam;
#endif

	void AssignPlayerTeam(AController* Controller);
	void SpawnPlayerArmy(AController* Controller);
};
