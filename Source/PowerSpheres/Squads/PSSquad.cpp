// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSSquad.h"
#include "PSSquadMemberComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/PSPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "PowerSpheres/PSPowerSphere.h"

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
		InitAbilitiesMapping();

		// We need at least a TotalUnitsNumber of 1 unit. The requirement is that we need to spawn at least a captain for the squad.
		// Also if we have special units in the squad, that number needs to be less than the total units. This way we allow squads
		// with only a captain and special units (without basic units) or an unit with only the captain (a hero or something similar).
		if (TotalUnitsNumber > 0 && TotalUnitsNumber > SpecialUnitsNumber)
		{
			BasicUnits.Empty();
			SpecialUnits.Empty();
			TArray<UPSSquadMemberComponent*> SquadMemberComponents;
			GetComponents<UPSSquadMemberComponent>(SquadMemberComponents);
			int UnitsSpawned = 0;
			FTransform SpawnTransform;

			// We spawn the captain first.
			SpawnTransform = FTransform(SquadMemberComponents[UnitsSpawned]->GetComponentRotation(), SquadMemberComponents[UnitsSpawned]->GetComponentLocation());
			CaptainUnit = SpawnUnit(CaptainUnitComposition, SpawnTransform);
			UnitsSpawned++;

			// Spawn the special units.
			for (int i = 0; i < SpecialUnitsNumber; i++)
			{
				SpawnTransform = FTransform(SquadMemberComponents[UnitsSpawned]->GetComponentRotation(), SquadMemberComponents[UnitsSpawned]->GetComponentLocation());
				SpecialUnits.Add(FSpecialUnitMap(i, SpawnUnit(SpecialUnitsComposition[i], SpawnTransform)));
				UnitsSpawned++;
			}

			// Spawn the rest of the squad as basic units.
			for (int i = 0; i < (TotalUnitsNumber - SpecialUnitsNumber - 1); i++)
			{
				SpawnTransform = FTransform(SquadMemberComponents[UnitsSpawned]->GetComponentRotation(), SquadMemberComponents[UnitsSpawned]->GetComponentLocation());
				BasicUnits.Add(SpawnUnit(BasicUnitComposition, SpawnTransform));
				UnitsSpawned++;
			}
		}
	}
}

APSUnit* APSSquad::SpawnUnit(FUnitComposition UnitComposition, FTransform UnitTransform)
{
	APSUnit* NewUnit = nullptr;
	UWorld* const World = GetWorld();
	if (World)
	{
		NewUnit = World->SpawnActorDeferred<APSUnit>(UnitComposition.UnitBlueprint, UnitTransform, this);
		if (NewUnit)
		{
			UPSPowerSphere* PowerSphere = UnitComposition.WeaponSlot.GetDefaultObject();
			if (PowerSphere)
			{
				UPSGameplayAbility* GameplayAbility = PowerSphere->GameplayAbility.GetDefaultObject();
				if (GameplayAbility && GameplayAbility->WeaponData && GameplayAbility->WeaponData->AbilityWeapon)
				{
					NewUnit->MeshMergeParameters.MeshesToMerge.Add(GameplayAbility->WeaponData->AbilityWeapon);
					NewUnit->EquippedWeaponData = GameplayAbility->WeaponData;
				}
			}

			NewUnit->Team = Team;
			NewUnit->PlayerOwner = PlayerOwner;
			NewUnit->FinishSpawning(UnitTransform);

			ConstructAbilities(UnitComposition, NewUnit);
		}
	}

	return NewUnit;
}

void APSSquad::InitAbilitiesMapping()
{
	if (AbilitiesMapping.Num() == 0)
	{
		for (uint8 i = 0; i <= (uint8)EAbilityType::MAX; i++)
		{
			AbilitiesMapping.Add((EAbilityType)i, FAbilityMappingSet());
		}
	}
}

void APSSquad::ConstructAbilities(FUnitComposition UnitComposition, APSUnit* NewUnit)
{
	TArray<TSubclassOf<class UPSPowerSphere>> PowerSpheres = TArray<TSubclassOf<class UPSPowerSphere>>();

	if (UnitComposition.MovementSlot)
	{
		UPSPowerSphere* MovementPowerSphere = UnitComposition.MovementSlot.GetDefaultObject();
		if (MovementPowerSphere)
		{
			AbilitiesMapping[EAbilityType::ActionMoveTo].UnitAbilityMap.Add(NewUnit, MovementPowerSphere->GameplayAbility);
		}
	}

	if (UnitComposition.WeaponSlot)
	{
		UPSPowerSphere* WeaponPowerSphere = UnitComposition.WeaponSlot.GetDefaultObject();
		if (WeaponPowerSphere)
		{
			AbilitiesMapping[EAbilityType::ActionEnemyUnit].UnitAbilityMap.Add(NewUnit, WeaponPowerSphere->GameplayAbility);
		}
	}

	PowerSpheres.Add(UnitComposition.MovementSlot);
	PowerSpheres.Add(UnitComposition.WeaponSlot);
	PowerSpheres.Append(UnitComposition.AbilitiesPowerSpheres);
	PowerSpheres.Append(UnitComposition.EffectsPowerSpheres);

	NewUnit->GivePowers(PowerSpheres);

	for (TSubclassOf<class UPSPowerSphere> PowerSphere : UnitComposition.AbilitiesPowerSpheres)
	{
		UPSPowerSphere* PowerSphereObject = PowerSphere.GetDefaultObject();
		if (PowerSphereObject)
		{
			EAbilityType AbilitySlot = EAbilityType::None;
			for (uint8 i = (uint8)EAbilityType::Ability1; i <= (uint8)EAbilityType::MAX; i++)
			{
				if (AbilitiesMapping[(EAbilityType)i].UnitAbilityMap.Num() == 0)
				{
					AbilitySlot = (EAbilityType)i;
					break;
				}
				else
				{
					if (AbilitiesMapping[(EAbilityType)i].UnitAbilityMap.FindKey(PowerSphereObject->GameplayAbility))
					{
						AbilitySlot = (EAbilityType)i;
						break;
					}
				}
			}
			AbilitiesMapping[AbilitySlot].UnitAbilityMap.Add(NewUnit, PowerSphereObject->GameplayAbility);
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
	DOREPLIFETIME(APSSquad, BasicUnits);
	DOREPLIFETIME(APSSquad, SpecialUnits);
	DOREPLIFETIME(APSSquad, CaptainUnit);
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

	TArray<UPSSquadMemberComponent*> SquadMemberComponents;
	GetComponents<UPSSquadMemberComponent>(SquadMemberComponents);

	TArray<UPSSquadMemberComponent*> OccupiedComponents = TArray<UPSSquadMemberComponent*>();

	// First I look for the component which is in the origin position of the squad and move the captain there.
	if (CaptainUnit)
	{
		for (UPSSquadMemberComponent* SquadMemberComponent : SquadMemberComponents)
		{
			if (SquadMemberComponent->GetRelativeTransform().GetLocation() == FVector::ZeroVector)
			{
				CaptainUnit->ActionMoveToLocation = SquadMemberComponent->GetComponentLocation();
				CaptainUnit->CurrentAbilityParams = FAbilityParams();
				OccupiedComponents.Add(SquadMemberComponent);
				CaptainUnit->UseAbility(EAbilityType::ActionMoveTo, bIsUserInput);
				break;
			}
		}
	}

	// I move the basic units right after the captain because with the current implementation they are going to
	// try to fill the most far away positions from the front of the squad.
	if (BasicUnits.Num() > 0)
	{
		TArray<APSUnit*> SortedUnits = BasicUnits;
		SortedUnits.Sort([this](const APSUnit& UnitA, const APSUnit& UnitB)
			{
				float DistanceA = FVector::DistSquared(UnitA.GetActorLocation(), this->GetActorLocation());
				float DistanceB = FVector::DistSquared(UnitB.GetActorLocation(), this->GetActorLocation());
				return DistanceA > DistanceB;
			});

		for (APSUnit* Unit : SortedUnits)
		{
			if (Unit)
			{
				SquadMemberComponents.Sort([Unit](const UPSSquadMemberComponent& ComponentA, const UPSSquadMemberComponent& ComponentB)
					{
						float DistanceA = FVector::DistSquared(ComponentA.GetComponentLocation(), Unit->GetActorLocation());
						float DistanceB = FVector::DistSquared(ComponentB.GetComponentLocation(), Unit->GetActorLocation());
						return DistanceA < DistanceB;
					});
				int i = 0;
				while (i < SquadMemberComponents.Num() && OccupiedComponents.Contains(SquadMemberComponents[i]))
				{
					i++;
				}

				Unit->ActionMoveToLocation = SquadMemberComponents[i]->GetComponentLocation();
				Unit->CurrentAbilityParams = FAbilityParams();

				OccupiedComponents.Add(SquadMemberComponents[i]);

				Unit->UseAbility(EAbilityType::ActionMoveTo, bIsUserInput);
			}
		}
	}

	// Then I move the special units to the closests positions behind the captain.
	if (SpecialUnits.Num() > 0)
	{
		TArray<FSpecialUnitMap> SortedSpecialUnits = SpecialUnits;
		SortedSpecialUnits.Sort([this](const FSpecialUnitMap SpecialUnitMapA, const FSpecialUnitMap SpecialUnitMapB)
			{
				float DistanceA = FVector::DistSquared(SpecialUnitMapA.Unit->GetActorLocation(), this->GetActorLocation());
				float DistanceB = FVector::DistSquared(SpecialUnitMapB.Unit->GetActorLocation(), this->GetActorLocation());
				return DistanceA > DistanceB;
			});

		for (FSpecialUnitMap SpecialUnit : SortedSpecialUnits)
		{
			if (SpecialUnit.Unit)
			{
				SquadMemberComponents.Sort([SpecialUnit](const UPSSquadMemberComponent& ComponentA, const UPSSquadMemberComponent& ComponentB)
					{
						float DistanceA = FVector::DistSquared(ComponentA.GetComponentLocation(), SpecialUnit.Unit->GetActorLocation());
						float DistanceB = FVector::DistSquared(ComponentB.GetComponentLocation(), SpecialUnit.Unit->GetActorLocation());
						return DistanceA < DistanceB;
					});
				int i = 0;
				while (i < SquadMemberComponents.Num() && OccupiedComponents.Contains(SquadMemberComponents[i]))
				{
					i++;
				}

				SpecialUnit.Unit->ActionMoveToLocation = SquadMemberComponents[i]->GetComponentLocation();
				SpecialUnit.Unit->CurrentAbilityParams = FAbilityParams();

				OccupiedComponents.Add(SquadMemberComponents[i]);

				SpecialUnit.Unit->UseAbility(EAbilityType::ActionMoveTo, bIsUserInput);
			}
		}
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
			TArray<APSUnit*> UnitsArray;
			AbilitiesMapping[AbilityType].UnitAbilityMap.GenerateKeyArray(UnitsArray);
			for (APSUnit* Unit : UnitsArray)
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

bool APSSquad::SquadDestroyed()
{
	TArray<APSUnit*> Units = GetAllUnits();
	return Units.Num() <= 0;
}

void APSSquad::UnitDied(APSUnit* Unit)
{
	RemoveUnitFromAbilitiesMapping(Unit);

	if (Unit == CaptainUnit)
	{
		CaptainUnit = nullptr;
		return;
	}
	
	bool UnitFound = false;
	int i = 0;
	while (!UnitFound && i < SpecialUnits.Num())
	{
		UnitFound = SpecialUnits[i].Unit == Unit;
		if (!UnitFound)
			i++;
	}
	if (UnitFound)
	{
		SpecialUnits.RemoveAt(i);
		return;
	}

	BasicUnits.Remove(Unit);
}

void APSSquad::RemoveUnitFromAbilitiesMapping(APSUnit* Unit)
{
	for (const TPair<EAbilityType, FAbilityMappingSet>& AbilitySet : AbilitiesMapping)
	{
		AbilitiesMapping[AbilitySet.Key].UnitAbilityMap.Remove(Unit);
	}
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
	TArray<APSUnit*> Units = TArray<APSUnit*>();

	// Add the captain first.
	if (CaptainUnit)
	{
		Units.Add(CaptainUnit);
	}

	// Add the special units in second place.
	for (FSpecialUnitMap UnitMap : SpecialUnits)
	{
		Units.Add(UnitMap.Unit);
	}

	// Add the rest of the units in the squad.
	Units.Append(BasicUnits);

	return Units;
}
