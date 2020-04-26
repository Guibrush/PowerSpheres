// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSTypes.h"
#include "PSStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSStaticLibrary : public UObject
{
	GENERATED_BODY()

public:

	/**
		It returns 0 or 1 depending on if the teams are enemies or not. It returns -1 in case
		one of the two teams is not valid or the calculation cannot be done for any other reason.
	*/
	UFUNCTION(BlueprintCallable)
	static int32 AreEnemyTeams(ETeamType FirstTeam, ETeamType SecondTeam);
	
};
