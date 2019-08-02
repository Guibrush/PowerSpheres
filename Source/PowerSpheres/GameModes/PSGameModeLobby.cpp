// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSGameModeLobby.h"
#include "Engine/World.h"
#include "Player/PSPlayerState.h"
#include "PSTypes.h"

bool APSGameModeLobby::StartGame(const FString& MapName, const FString& Options, bool bSeamless)
{
	if (UWorld* World = GetWorld())
	{
		bUseSeamlessTravel = bSeamless;
		FString FinalURL;
		FinalURL = MapName + "?Game=" + DefaultGameMode->GetPathName() + "?" + Options;
		return World->ServerTravel(FinalURL, false);
	}

	return false;
}

void APSGameModeLobby::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);

	if (APSPlayerState* PlayerState = Cast<APSPlayerState>(C->PlayerState))
	{
		PlayerState->Team = ETeamType::Team1;
	}
}
