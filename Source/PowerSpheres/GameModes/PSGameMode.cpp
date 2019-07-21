// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#include "PSGameMode.h"
#include "Player/PSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

APSGameMode::APSGameMode()
{

}

void APSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	Teams.Empty();

	Teams.Add(ETeamType::Team1, FPlayerControllersTeam());
	Teams.Add(ETeamType::Team2, FPlayerControllersTeam());

#if WITH_EDITOR
	CurrentTeam = ETeamType::Team1;
#endif
}

FString APSGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	APSPlayerController* PSController = Cast<APSPlayerController>(NewPlayerController);
	if (PSController)
	{
		ETeamType Team = (ETeamType)UGameplayStatics::GetIntOption(Options, TEXT("Team"), 0);
		if (Team > ETeamType::NoTeam)
		{
			PSController->Team = Team;
			Teams[Team].Team.Add(PSController);
		}
#if WITH_EDITOR
		else
		{
			PSController->Team = CurrentTeam;
			Teams[CurrentTeam].Team.Add(PSController);

			if (CurrentTeam == ETeamType::Team1)
				CurrentTeam = ETeamType::Team2;
			else if (CurrentTeam == ETeamType::Team2)
				CurrentTeam = ETeamType::Team1;
		}
#endif
	}

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void APSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UWorld* const World = GetWorld();
	APSPlayerController* PSPlayerController = Cast<APSPlayerController>(NewPlayer);
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
