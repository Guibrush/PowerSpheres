// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSStaticLibrary.h"

int32 UPSStaticLibrary::AreEnemyTeams(ETeamType FirstTeam, ETeamType SecondTeam)
{
	if (FirstTeam > ETeamType::NoTeam && SecondTeam > ETeamType::NoTeam)
	{
		if (FirstTeam == SecondTeam)
		{
			// Both teams were the same.
			return false;
		}
		else
		{
			if (FirstTeam > ETeamType::AI)
			{
				if (SecondTeam > ETeamType::AI)
				{
					// Both teams are players or neutral.
					return false;
				}
				else
				{
					// First team is a player or neutral and second team is AI.
					return true;
				}
			}
			else
			{
				if (SecondTeam > ETeamType::AI)
				{
					// First team is AI and second team is player or neutral.
					return true;
				}
				else
				{
					// Both teams are AI.
					return false;
				}
			}
		}
	}

	// Some of the teams were invalid or any other thing has gone wrong.
	return -1;
}