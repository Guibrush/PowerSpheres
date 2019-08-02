// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSPlayerState.h"
#include "Net/UnrealNetwork.h"

void APSPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (APSPlayerState* PSPlayerState = Cast<APSPlayerState>(PlayerState))
	{
		PSPlayerState->Team = Team;
	}
}

void APSPlayerState::TeamChangedByUser(ETeamType NewTeam)
{
	ChangeTeam(NewTeam);
}

void APSPlayerState::ChangeTeam_Implementation(ETeamType NewTeam)
{
	Team = NewTeam;
}

bool APSPlayerState::ChangeTeam_Validate(ETeamType NewTeam)
{
	return true;
}

void APSPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APSPlayerState, Team);
}
