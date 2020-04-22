// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#include "PSGameMode.h"
#include "Player/PSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PSPlayerState.h"
#include "Player/PSPlayerStart.h"
#include "PowerSpheres/PSPowerSphereCrateSpawnerManager.h"
#include "PowerSpheres/PSPowerSphereCrateSpawner.h"
#include "PSGameState.h"

APSGameMode::APSGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void APSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// TODO: This shall be singleton access
	PowerSphereCrateSpawnerManager = NewObject<UPSPowerSphereCrateSpawnerManager>();

#if WITH_EDITOR
	CurrentTeam = ETeamType::Team1;
#endif
}

FString APSGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	AssignPlayerTeam(NewPlayerController);

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void APSGameMode::InitSeamlessTravelPlayer(AController* NewController)
{
	AssignPlayerTeam(NewController);

	Super::InitSeamlessTravelPlayer(NewController);
}

//void APSGameMode::PostLogin(APlayerController* NewPlayer)
//{
//	Super::PostLogin(NewPlayer);
//
//	SpawnPlayerArmy(NewPlayer);
//}
//
//void APSGameMode::HandleSeamlessTravelPlayer(AController*& C)
//{
//	Super::HandleSeamlessTravelPlayer(C);
//
//	SpawnPlayerArmy(C);
//}

void APSGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	SpawnPlayerArmy(NewPlayer);
}

void APSGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

#if WITH_EDITOR
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	APSPlayerStart* EnemyPlayerStart = nullptr;
	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSPlayerStart::StaticClass(), FoundPlayerStarts);
	for (AActor* PlayerStart : FoundPlayerStarts)
	{
		APSPlayerStart* PSPlayerStart = Cast<APSPlayerStart>(PlayerStart);
		if (PSPlayerStart && PSPlayerStart->Team == ETeamType::AI)
		{
			EnemyPlayerStart = PSPlayerStart;
			break;
		}
	}

	if (!EnemyPlayerStart)
	{
		return;
	}

	FVector StartLocation = EnemyPlayerStart->GetActorLocation();
	FRotator StartRotation = EnemyPlayerStart->GetActorRotation();
	for (TSubclassOf<APSSquad> EnemySquadBlueprint : EnemySquadsToPIE)
	{
		FTransform StartTransform = FTransform(StartRotation, StartLocation);
		APSSquad* NewSquad = World->SpawnActorDeferred<APSSquad>(EnemySquadBlueprint, StartTransform, GetOwner());
		if (NewSquad)
		{
			NewSquad->Team = ETeamType::AI;
			NewSquad->PlayerOwner = nullptr;
			NewSquad->FinishSpawning(StartTransform);
		}
	}
#endif
}


void APSGameMode::StartPlay()
{
	Super::StartPlay();
	if (!PowerSphereCrateSpawnerManager.IsValid()) { return; }
	for (APSPowerSphereCrateSpawner* Spawner : PowerSphereCrateSpawnerManager->GetCrateSpawners())
	{
		if(!Spawner) { continue; }
		Spawner->TryToSpawnCrate();
	}
}

void APSGameMode::AssignPlayerTeam(AController* Controller)
{
	if (APSPlayerController * PSController = Cast<APSPlayerController>(Controller))
	{
		APSPlayerState* PSPlayerState = Cast<APSPlayerState>(Controller->PlayerState);
		if (PSPlayerState && PSPlayerState->Team > ETeamType::NoTeam)
		{
			PSController->Team = PSPlayerState->Team;
		}

#if WITH_EDITOR
		else
		{
			PSController->Team = CurrentTeam;

			if (CurrentTeam == ETeamType::Team1)
				CurrentTeam = ETeamType::Team2;
			else if (CurrentTeam == ETeamType::Team2)
				CurrentTeam = ETeamType::Team1;
		}
#endif
	}
}

void APSGameMode::SpawnPlayerArmy(AController* Controller)
{
	UWorld* const World = GetWorld();
	APSPlayerController* PSPlayerController = Cast<APSPlayerController>(Controller);
	if (World && PSPlayerController)
	{
		FVector StartLocation = PSPlayerController->StartSpot->GetActorLocation();
		FRotator StartRotation = PSPlayerController->StartSpot->GetActorRotation();
		for (TSubclassOf<APSSquad> SquadBlueprint : PSPlayerController->SquadsToPIE)
		{
			FTransform StartTransform = FTransform(StartRotation, StartLocation);
			APSSquad* NewSquad = World->SpawnActorDeferred<APSSquad>(SquadBlueprint, StartTransform, GetOwner());
			if (NewSquad)
			{
				NewSquad->Team = PSPlayerController->Team;
				NewSquad->PlayerOwner = PSPlayerController;
				NewSquad->FinishSpawning(StartTransform);
			}
		}
	}
}
