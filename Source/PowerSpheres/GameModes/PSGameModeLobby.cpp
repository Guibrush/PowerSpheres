// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSGameModeLobby.h"
#include "Engine/World.h"

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
