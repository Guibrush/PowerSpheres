// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSSquad.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/PSPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "PowerSpheres/PSPowerSphereData.h"

// Sets default values
APSSquad::APSSquad()
{
	GetCapsuleComponent()->InitCapsuleSize(0.f, 0.f);

	GetCharacterMovement()->Deactivate();

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APSSquad::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (TotalUnitsNumber > 0)
		{
			ConstructAbilities();

			GenerateValidUnitsDirections();

			TArray<TSubclassOf<class UPSPowerSphereData>> PowerSpheres;
			SquadEquipment.AbilitiesSlots.GenerateValueArray(PowerSpheres);
			PowerSpheres.Append(SquadEquipment.Effects);

			UnitList.Empty();
			FTransform SpawnTransform;
			for (int i = 0; i < TotalUnitsNumber; i++)
			{
				if (i == 0)
				{
					SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
				}
				else
				{
					FVector SpawnLocation = GetActorLocation() + ValidUnitsDirection[i];

					SpawnTransform = FTransform(GetActorRotation(), SpawnLocation);
				}

				UnitList.Add(SpawnUnit(SpawnTransform, PowerSpheres));
			}
		}
	}
}

APSUnit* APSSquad::SpawnUnit(FTransform UnitTransform, TArray<TSubclassOf<class UPSPowerSphereData>> PowerSpheres)
{
	APSUnit* NewUnit = nullptr;
	UWorld* const World = GetWorld();
	if (World)
	{
		NewUnit = World->SpawnActorDeferred<APSUnit>(UnitBlueprint, UnitTransform, this);
		if (NewUnit)
		{
			if (SquadEquipment.AbilitiesSlots.Find(EAbilityType::ActionEnemyUnit))
			{
				UPSPowerSphereData* PowerSphere = SquadEquipment.AbilitiesSlots[EAbilityType::ActionEnemyUnit].GetDefaultObject();
				if (PowerSphere)
				{
					UPSGameplayAbility* GameplayAbility = PowerSphere->GameplayAbility.GetDefaultObject();
					if (GameplayAbility && GameplayAbility->WeaponData && GameplayAbility->WeaponData->AbilityWeapon)
					{
						NewUnit->MeshMergeParameters.MeshesToMerge.Add(GameplayAbility->WeaponData->AbilityWeapon);
						NewUnit->EquippedWeaponData = GameplayAbility->WeaponData;
					}
				}
			}

			NewUnit->Team = Team;
			NewUnit->PlayerOwner = PlayerOwner;
			NewUnit->Squad = this;
			NewUnit->FinishSpawning(UnitTransform);

			NewUnit->GivePowers(PowerSpheres);
		}
	}

	return NewUnit;
}

void APSSquad::ConstructAbilities()
{
	SquadAbilities.Empty();

	for (auto& Elem : SquadEquipment.AbilitiesSlots)
	{
		UPSPowerSphereData* AbilityPowerSphere = Elem.Value.GetDefaultObject();
		if (AbilityPowerSphere)
		{
			SquadAbilities.Add(Elem.Key, AbilityPowerSphere->GameplayAbility);
		}
	}
}

void APSSquad::GenerateValidUnitsDirections()
{
	for (int i = 0; i < TotalUnitsNumber; i++)
	{
		FVector TempDirection;
		FVector TempLocation;
		bool ValidLocation = false;
		while (!ValidLocation)
		{
			TempDirection = GetActorForwardVector() * -1.0f;
			TempDirection = TempDirection.RotateAngleAxis(FMath::RandRange(-90.0f, 90.0f), FVector::UpVector);
			TempDirection *= DistanceBetweenUnits + FMath::RandRange(0.0f, DistanceBetweenUnits);
			TempLocation = GetActorLocation() + TempDirection;
			ValidLocation = true;
			for (FVector ValidDirection : ValidUnitsDirection)
			{
				FVector ValidPosition = GetActorLocation() + ValidDirection;
				float DistanceToSpawn = (TempLocation - ValidPosition).Size();
				if (DistanceToSpawn < DistanceBetweenUnits)
				{
					ValidLocation = false;
					break;
				}
			}
		}

		ValidUnitsDirection.Add(TempDirection);
	}
}

void APSSquad::EquipSphere(TSubclassOf<class UPSPowerSphereData> NewSphere)
{
	UPSPowerSphereData* NewPowerSphere = NewSphere.GetDefaultObject();
	if (NewPowerSphere && NewPowerSphere->AbilityType > EAbilityType::None)
	{
		SquadEquipment.AbilitiesSlots.Add(NewPowerSphere->AbilityType, NewSphere);
		SquadAbilities.Add(NewPowerSphere->AbilityType, NewPowerSphere->GameplayAbility);
	}
	else
	{
		SquadEquipment.Effects.Add(NewSphere);
	}

	TArray<TSubclassOf<class UPSPowerSphereData>> PowerSpheres;
	PowerSpheres.Add(NewSphere);
	TArray<APSUnit*> Units = GetAllUnits();
	for (APSUnit* Unit : Units)
	{
		if (Unit)
		{
			Unit->GivePowers(PowerSpheres);
		}
	}
}

// Called every frame
void APSSquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APSSquad::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APSSquad::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APSSquad, Team);
	DOREPLIFETIME(APSSquad, PlayerOwner);
	DOREPLIFETIME(APSSquad, UnitList);
	DOREPLIFETIME(APSSquad, SquadAbilities);
	DOREPLIFETIME(APSSquad, SquadEquipment);
}

void APSSquad::MoveSquad(const FVector DestLocation, const FRotator DestRotation, bool bIsUserInput)
{
	FRotator MovementRotation = DestRotation;
	if (MovementRotation == FRotator::ZeroRotator)
	{
		MovementRotation = (DestLocation - GetActorLocation()).Rotation();
	}
	SetActorLocation(DestLocation);
	SetActorRotation(MovementRotation);

	ValidUnitsDirection.Empty();
	GenerateValidUnitsDirections();

	TArray<APSUnit*> Units = GetAllUnits();
	int i = 0;
	for (APSUnit* Unit : Units)
	{
		if (i == 0)
		{
			Unit->ActionMoveToLocation = GetActorLocation();
		}
		else
		{
			Unit->ActionMoveToLocation = GetActorLocation() + ValidUnitsDirection[i];
		}
		Unit->CurrentAbilityParams = FAbilityParams();

		Unit->UseAbility(EAbilityType::ActionMoveTo, bIsUserInput);

		i++;
	}
}

void APSSquad::SquadSelectedClient_Implementation()
{
	TArray<APSUnit*> Units = GetAllUnits();
	for (APSUnit* Unit : Units)
	{
		if (Unit)
		{
			Unit->UnitSelectedClient();
		}
	}
}

void APSSquad::SquadDeselectedClient_Implementation()
{
	TArray<APSUnit*> Units = GetAllUnits();
	for (APSUnit* Unit : Units)
	{
		if (Unit)
		{
			Unit->UnitDeselectedClient();
		}
	}
}

void APSSquad::UseSquadAbility(EAbilityType AbilityType, FAbilityParams AbilityParams, bool bIsUserInput)
{
	if (HasAuthority())
	{
		if (AbilityType == EAbilityType::ActionMoveTo)
		{
			MoveSquad(AbilityParams.Position, AbilityParams.Rotation, bIsUserInput);
		}
		else
		{
			if (SquadAbilities.Find(AbilityType))
			{
				TArray<APSUnit*> Units = GetAllUnits();
				for (APSUnit* Unit : Units)
				{
					if (Unit)
					{
						CurrentAbilityParams = AbilityParams;
						Unit->CurrentAbilityParams = AbilityParams;
						Unit->UseAbility(AbilityType, bIsUserInput);
					}
				}
			}
		}
	}
}

void APSSquad::CancelCurrentSquadAbility()
{
	if (HasAuthority())
	{
		TArray<APSUnit*> Units = GetAllUnits();
		for (APSUnit* Unit : Units)
		{
			Unit->CancelCurrentAbility();
		}

		CurrentAbilityParams = FAbilityParams();
	}
}

bool APSSquad::SquadDestroyed()
{
	TArray<APSUnit*> Units = GetAllUnits();
	return Units.Num() <= 0;
}

void APSSquad::UnitDied(APSUnit* Unit)
{
	UnitList.Remove(Unit);
}

void APSSquad::TargetSquadDestroyed(APSSquad* TargetSquad)
{
	if (HasAuthority() && TargetSquad && TargetSquad == CurrentAbilityParams.Actor)
	{
		TArray<APSUnit*> Units = GetAllUnits();
		for (APSUnit* Unit : Units)
		{
			Unit->TargetSquadDestroyed(TargetSquad);
		}
	}
}

TArray<APSUnit*> APSSquad::GetAllUnits()
{
	return UnitList;
}
