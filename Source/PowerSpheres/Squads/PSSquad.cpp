// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSSquad.h"
#include "PSSquadMemberComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

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
		Units.Empty();
		TArray<UPSSquadMemberComponent*> SquadMemberComponents;
		GetComponents<UPSSquadMemberComponent>(SquadMemberComponents);
		for (UPSSquadMemberComponent* SquadMemberComp : SquadMemberComponents)
		{
			UWorld* const World = GetWorld();
			if (World)
			{
				FTransform ComponentTransform = FTransform(SquadMemberComp->GetComponentRotation(), SquadMemberComp->GetComponentLocation());
				APSUnit* Unit = World->SpawnActorDeferred<APSUnit>(SquadMemberComp->UnitBlueprint, ComponentTransform, this);
				if (Unit)
				{
					Unit->Team = Team;
					Unit->PlayerOwner = PlayerOwner;
					Unit->FinishSpawning(ComponentTransform);
					Units.Add(Unit);

					for (const TPair<EAbilityType, TSubclassOf<class UPSGameplayAbility>>& Ability : CommonAbilities)
					{
						Unit->GiveAbility(Ability.Value);
					}
				}
			}
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
	DOREPLIFETIME(APSSquad, Units);
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

	TArray<APSUnit*> SortedUnits = Units;
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

			OccupiedComponents.Add(SquadMemberComponents[i]);

			Unit->UseAbility(CommonAbilities[EAbilityType::ActionMoveTo], bIsUserInput);
		}
	}
}

void APSSquad::SquadSelectedClient_Implementation()
{
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
			for (APSUnit* Unit : Units)
			{
				CurrentAbilityParams = AbilityParams;
				Unit->CurrentAbilityParams = AbilityParams;
				Unit->UseAbility(CommonAbilities[AbilityType], bIsUserInput);
			}
		}
	}
}

bool APSSquad::SquadDestroyed()
{
	return Units.Num() <= 0;
}

void APSSquad::UnitDied(APSUnit* Unit)
{
	Units.Remove(Unit);
}

void APSSquad::TargetSquadDestroyed(APSSquad* TargetSquad)
{
	if (HasAuthority() && TargetSquad && TargetSquad == CurrentAbilityParams.Actor)
	{
		for (APSUnit* Unit : Units)
		{
			Unit->TargetSquadDestroyed(TargetSquad);
		}
	}
}
