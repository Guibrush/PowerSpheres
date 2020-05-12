// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSTypes.h"
#include "GAS/PSGameplayAbility.h"
#include "PSSquad.generated.h"

class UPSSquadMemberComponent;

UCLASS()
class POWERSPHERES_API APSSquad : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APSSquad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void MoveSquad(const FVector DestLocation, const FRotator DestRotation, bool bIsUserInput);

	/** This function gets called only on the client who selected this squad. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void SquadSelectedClient();

	/** This function gets called only on the client who deselected this squad. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void SquadDeselectedClient();

	UFUNCTION(BlueprintCallable)
	void UseSquadAbility(EAbilityType AbilityType, FAbilityParams AbilityParams, bool bIsUserInput);

	UFUNCTION(BlueprintCallable)
	void CancelCurrentSquadAbility();

	/** Whether all the units of this squad had been killed or not. */
	UFUNCTION(BlueprintCallable)
	bool SquadDestroyed();

	/** Blueprint event for when an unit of this squad has been damaged. */
	UFUNCTION(BlueprintImplementableEvent)
	void SquadDamagedEvent(APSUnit* Unit, APSUnit* Attacker, FGameplayCueParameters Params);

	UFUNCTION(BlueprintCallable)
	void EquipSphere(TSubclassOf<class UPSPowerSphere> NewSphere);

	/** Gets all the units in this squad in a single array. */
	UFUNCTION(BlueprintPure)
	TArray<APSUnit*> GetAllUnits();

	// Called when one of the units from this squad dies.
	UFUNCTION()
	void UnitDied(APSUnit* Unit);

	UFUNCTION()
	void TargetSquadDestroyed(APSSquad* TargetSquad);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition)
	int TotalUnitsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition)
	TSubclassOf<class APSUnit> UnitBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition, Replicated)
	FSquadEquipment SquadEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SquadComposition)
	float DistanceBetweenUnits;

	UPROPERTY(BlueprintReadOnly, Replicated)
	ETeamType Team;

	UPROPERTY(BlueprintReadOnly, Replicated)
	class APSPlayerController* PlayerOwner;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<APSUnit*> UnitList;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FAbilityParams CurrentAbilityParams;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TMap<EAbilityType, TSubclassOf<class UPSGameplayAbility>> SquadAbilities;

protected:

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

private:

	TArray<FVector> ValidUnitsDirection;

	APSUnit* SpawnUnit(FTransform UnitTransform, TArray<TSubclassOf<class UPSPowerSphere>> PowerSpheres);

	void ConstructAbilities();

	void GenerateValidUnitsDirections();

};
