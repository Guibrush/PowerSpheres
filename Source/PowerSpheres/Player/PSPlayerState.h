// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PSTypes.h"
#include "PSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API APSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	/** Team of this player. */
	UPROPERTY(Replicated, BlueprintReadOnly, Category=PSPlayerState)
	ETeamType Team;

	/** Function to be called by the local user or player controller to change the team. WARNING - This functionality is only supported in the lobby at the moment. */
	UFUNCTION(BlueprintCallable, Category=PSPlayerState)
	void TeamChangedByUser(ETeamType NewTeam);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:

	//~ Begin APlayerState Interface
	virtual void CopyProperties(APlayerState* PlayerState) override;
	//~ End APlayerState Interface

	UFUNCTION(Server, Reliable, WithValidation)
	void ChangeTeam(ETeamType NewTeam);
	
};
