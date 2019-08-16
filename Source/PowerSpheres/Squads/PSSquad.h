// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSTypes.h"
#include "GAS/PSGameplayAbility.h"
#include "PSSquad.generated.h"

USTRUCT(BlueprintType)
struct POWERSPHERES_API FAbilityMappingSet
{
	GENERATED_USTRUCT_BODY()

	FAbilityMappingSet()
		: UnitAbilityMap(TMap<APSUnit*, TSubclassOf<class UPSGameplayAbility>>())
	{ }

	UPROPERTY(BlueprintReadOnly)
	TMap<APSUnit*, TSubclassOf<class UPSGameplayAbility>> UnitAbilityMap;
};

USTRUCT(BlueprintType)
struct POWERSPHERES_API FSpecialUnitMap
{
	GENERATED_USTRUCT_BODY()

	FSpecialUnitMap()
		: UnitIndex(0)
		, Unit(nullptr)
	{ }

	FSpecialUnitMap(int NewUnitIndex, APSUnit* NewUnit)
		: UnitIndex(NewUnitIndex)
		, Unit(NewUnit)
	{ }

	UPROPERTY(BlueprintReadOnly)
	int UnitIndex;

	UPROPERTY(BlueprintReadOnly)
	APSUnit* Unit;
};

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

	UFUNCTION()
	void UseSquadAbility(EAbilityType AbilityType, FAbilityParams AbilityParams, bool bIsUserInput);

	/** Whether all the units of this squad had been killed or not. */
	UFUNCTION(BlueprintCallable)
	bool SquadDestroyed();

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
	int SpecialUnitsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition)
	FUnitComposition CaptainUnitComposition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition)
	FUnitComposition BasicUnitComposition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SquadComposition)
	TArray<FUnitComposition> SpecialUnitsComposition;

	UPROPERTY(BlueprintReadOnly, Replicated)
	ETeamType Team;

	UPROPERTY(BlueprintReadOnly, Replicated)
	class APSPlayerController* PlayerOwner;

	UPROPERTY(BlueprintReadOnly, Replicated)
	APSUnit* CaptainUnit;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<APSUnit*> BasicUnits;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<FSpecialUnitMap> SpecialUnits;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FAbilityParams CurrentAbilityParams;

	/** 
	This structure is too complex to replicate it to the client. We need to use another
	data structure to replicate this information to the client.
	*/
	UPROPERTY(BlueprintReadOnly)
	TMap<EAbilityType, FAbilityMappingSet> AbilitiesMapping;

protected:

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

private:

	APSUnit* SpawnUnit(FUnitComposition UnitComposition, FTransform UnitTransform);

	void InitAbilitiesMapping();

	void ConstructAbilities(FUnitComposition UnitComposition, APSUnit* NewUnit);

	void RemoveUnitFromAbilitiesMapping(APSUnit* Unit);

};
