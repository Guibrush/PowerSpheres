// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Units/PSUnit.h"
#include "Squads/PSSquad.h"
#include "PSTypes.h"
#include "Formations/PSFormation.h"
#include "PSPlayerController.generated.h"

UCLASS()
class APSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APSPlayerController();

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Proxy function called from the client version of the squad to request the abilities mapping data. */
	UFUNCTION(Server, Reliable, WithValidation)
	void RequestSquadAbilitiesMappingServer(APSSquad* Squad);

	/** Proxy function called from the server version of the squad to send the data to the client. */
	UFUNCTION(Client, Reliable)
	void ReceivedSquadAbilitiesMappingSetClient(APSSquad* Squad, EAbilityType NewAbilityType, FAbilityMappingSet NewAbilityMappingSet);

	/** Squad blueprints used for PIE. WARNING: ONLY FOR TESTING PURPOSES. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APSSquad>> SquadsToPIE;

	/** Squads currently selected by the player. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<APSSquad*> SelectedSquads;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APSFormation> FormationBlueprint;

	UPROPERTY(BlueprintReadOnly)
	APSFormation* Formation;

	UPROPERTY(BlueprintReadOnly, Replicated)
	ETeamType Team;

protected:

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	/** Input handlers for the mouse buttons. */
	void OnActionPressed();
	void OnActionReleased();

	void OnSelectPressed();
	void OnSelectReleased();

	void OnUnitAbilityPressed();
	void OnUnitAbilityReleased();

	/** Input handlers for moving the character(camera) around and zoom in and out. */
	void MoveForward(float Val);
	void MoveRight(float Val);
	void ZoomIn(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
	void SelectSquads(const TArray<APSSquad*>& Squads);

	UFUNCTION(Server, Reliable, WithValidation)
	void UseSelectedSquadsAbility(EAbilityType AbilityType, FAbilityParams AbilityParams);

	UFUNCTION(Server, Reliable, WithValidation)
	void UseSingleSquadAbility(APSSquad* Squad, EAbilityType AbilityType, FAbilityParams AbilityParams);

private:

	/** Actor representing the fog of war in the map. */
	class AMapFog* MapFog;
};


