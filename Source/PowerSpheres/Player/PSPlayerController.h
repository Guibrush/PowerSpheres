// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Units/PSUnit.h"
#include "Squads/PSSquad.h"
#include "PSTypes.h"
#include "Formations/PSFormation.h"
#include "PSPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FSquadSelectedSignature, APSPlayerController, OnSquadSelected, APSSquad*, Squad);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FSquadDeselectedSignature, APSPlayerController, OnSquadDeselected, APSSquad*, Squad);

UCLASS()
class APSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APSPlayerController();

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	UPROPERTY(BlueprintReadOnly)
	AActor* ActorUnderCursor;

	UPROPERTY(BlueprintAssignable)
	FSquadSelectedSignature OnSquadSelected;

	UPROPERTY(BlueprintAssignable)
	FSquadDeselectedSignature OnSquadDeselected;

	UFUNCTION(BlueprintCallable)
	void SelectSquads(const TArray<APSSquad*> Squads);

	UFUNCTION(BlueprintCallable)
	void UseAbility(EAbilityType AbilityType);

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

	void Ability1Pressed();
	void Ability1Released();

	void Ability2Pressed();
	void Ability2Released();

	void Ability3Pressed();
	void Ability3Released();

	void Ability4Pressed();
	void Ability4Released();

	/** Input handlers for moving the character(camera) around and zoom in and out. */
	void MoveForward(float Val);
	void MoveRight(float Val);
	void ZoomIn(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSelectSquads(const TArray<APSSquad*>& Squads);

	UFUNCTION(Server, Reliable, WithValidation)
	void UseSelectedSquadsAbility(EAbilityType AbilityType, FAbilityParams AbilityParams);

	UFUNCTION(Server, Reliable, WithValidation)
	void UseSingleSquadAbility(APSSquad* Squad, EAbilityType AbilityType, FAbilityParams AbilityParams);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerTryToOpenPSCrate(class APSPowerSphereCrate* PSCrate);

private:

	/** Actor representing the fog of war in the map. */
	class AMapFog* MapFog;
};


