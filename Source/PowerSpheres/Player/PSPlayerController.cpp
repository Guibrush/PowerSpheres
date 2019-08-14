// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#include "PSPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PSCharacter.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "UI/PSHUD.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"
#include "EngineUtils.h"
#include "MapFog.h"

APSPlayerController::APSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void APSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void APSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Action", IE_Pressed, this, &APSPlayerController::OnActionPressed);
	InputComponent->BindAction("Action", IE_Released, this, &APSPlayerController::OnActionReleased);

	InputComponent->BindAction("Select", IE_Pressed, this, &APSPlayerController::OnSelectPressed);
	InputComponent->BindAction("Select", IE_Released, this, &APSPlayerController::OnSelectReleased);

	InputComponent->BindAction("UnitAbility", IE_Pressed, this, &APSPlayerController::OnUnitAbilityPressed);
	InputComponent->BindAction("UnitAbility", IE_Released, this, &APSPlayerController::OnUnitAbilityReleased);

	InputComponent->BindAxis("MoveForward", this, &APSPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APSPlayerController::MoveRight);
	InputComponent->BindAxis("ZoomIn", this, &APSPlayerController::ZoomIn);
}

void APSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		Formation = World->SpawnActor<APSFormation>(FormationBlueprint, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		for (TActorIterator<AMapFog> ActorItr(World); ActorItr; ++ActorItr)
		{
			MapFog = *ActorItr;
			// It should be only one AMapFog actor in the map, so as soon as we find the first one we break the for loop.
			break;
		}
	}
}

void APSPlayerController::OnActionPressed()
{

}

void APSPlayerController::OnActionReleased()
{
	if (SelectedSquads.Num() > 0)
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			APSUnit* PSUnit = Cast<APSUnit>(Hit.GetActor());
			if (PSUnit && !PSUnit->CoveredByFOW)
			{
				// Hit an unit.
				FAbilityParams AbilityParams = FAbilityParams();
				AbilityParams.Actor = PSUnit->Squad;
				if (PSUnit->Squad->Team != Team)
				{
					// Hit enemy squad.
					UseSelectedSquadsAbility(EAbilityType::ActionEnemyUnit, AbilityParams);
				}
				else
				{
					// Hit friendly squad (doesn't matter the player owner for now).
					UseSelectedSquadsAbility(EAbilityType::ActionFriendlyUnit, AbilityParams);
				}
			}
			else
			{
				// Hit a place where we can try to move.
				if (SelectedSquads.Num() > 1)
				{
					FRotator FormationRotation = (Hit.ImpactPoint - Formation->GetActorLocation()).Rotation();
					Formation->SetActorLocation(Hit.ImpactPoint);
					Formation->SetActorRotation(FormationRotation);
					int i = 0;
					for (APSSquad* Squad : SelectedSquads)
					{
						FAbilityParams AbilityParams = FAbilityParams();
						AbilityParams.Position = Formation->FormationPositions[i]->GetComponentLocation();
						AbilityParams.Rotation = Formation->GetActorRotation();
						UseSingleSquadAbility(Squad, EAbilityType::ActionMoveTo, AbilityParams);
						i++;
					}
				}
				else
				{
					FAbilityParams AbilityParams = FAbilityParams();
					AbilityParams.Position = Hit.ImpactPoint;
					UseSelectedSquadsAbility(EAbilityType::ActionMoveTo, AbilityParams);
				}
			}
		}
	}
}

void APSPlayerController::OnSelectPressed()
{
	APSHUD* HUD = Cast<APSHUD>(GetHUD());
	if (HUD)
	{
		HUD->StartSelectionRectangle();
	}
}

void APSPlayerController::OnSelectReleased()
{
	if (SelectedSquads.Num() > 0)
	{
		for (APSSquad* Squad : SelectedSquads)
		{
			Squad->SquadDeselectedClient();
		}

		SelectedSquads.Empty();
	}

	TArray<APSUnit*> SelectedUnits;
	APSHUD* HUD = Cast<APSHUD>(GetHUD());
	if (HUD)
	{
		SelectedUnits = HUD->FinishSelectionRectangle();
	}

	if (SelectedUnits.Num() > 0)
	{
		for (APSUnit* Unit : SelectedUnits)
		{
			SelectedSquads.AddUnique(Unit->Squad);
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.IsValidBlockingHit() && Hit.GetActor())
		{
			APSUnit* UnitHit = Cast<APSUnit>(Hit.GetActor());
			if (UnitHit && UnitHit->Squad)
			{
				if (UnitHit->Team == Team && UnitHit->PlayerOwner == this)
				{
					SelectedSquads.Add(UnitHit->Squad);
				}
				else
				{
					// TODO: Select enemy's or other team member's squads.
				}
			}
		}
	}

	if (SelectedSquads.Num() > 0)
	{
		for (APSSquad* Squad : SelectedSquads)
		{
			Squad->SquadSelectedClient();
		}
	}

	//for (APowerSpheresSquad* Squad : SelectedSquads)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Selected Squad: %s"), *Squad->GetHumanReadableName()));
	//}

	SelectSquads(SelectedSquads);
}

void APSPlayerController::OnUnitAbilityPressed()
{

}

void APSPlayerController::OnUnitAbilityReleased()
{

}

void APSPlayerController::SelectSquads_Implementation(const TArray<APSSquad*>& Squads)
{
	SelectedSquads = Squads;
}

bool APSPlayerController::SelectSquads_Validate(const TArray<APSSquad*>& Squads)
{
	return true;
}

void APSPlayerController::UseSelectedSquadsAbility_Implementation(EAbilityType AbilityType, FAbilityParams AbilityParams)
{
	if (SelectedSquads.Num() > 0)
	{
		for (APSSquad* Squad : SelectedSquads)
		{
			Squad->UseSquadAbility(AbilityType, AbilityParams, true);
		}
	}
}

bool APSPlayerController::UseSelectedSquadsAbility_Validate(EAbilityType AbilityType, FAbilityParams AbilityParams)
{
	return true;
}

void APSPlayerController::UseSingleSquadAbility_Implementation(APSSquad* Squad, EAbilityType AbilityType, FAbilityParams AbilityParams)
{
	Squad->UseSquadAbility(AbilityType, AbilityParams, true);
}

bool APSPlayerController::UseSingleSquadAbility_Validate(APSSquad* Squad, EAbilityType AbilityType, FAbilityParams AbilityParams)
{
	return true;
}

void APSPlayerController::MoveForward(float Val)
{
	APSCharacter* PSCharacter = Cast<APSCharacter>(GetPawn());
	if (PSCharacter)
	{
		PSCharacter->MoveForward(Val);
	}
}

void APSPlayerController::MoveRight(float Val)
{
	APSCharacter* PSCharacter = Cast<APSCharacter>(GetPawn());
	if (PSCharacter)
	{
		PSCharacter->MoveRight(Val);
	}
}

void APSPlayerController::ZoomIn(float Val)
{
	APSCharacter* PSCharacter = Cast<APSCharacter>(GetPawn());
	if (PSCharacter)
	{
		PSCharacter->ZoomIn(Val);
	}
}

void APSPlayerController::RequestSquadAbilitiesMappingServer_Implementation(APSSquad* Squad)
{
	Squad->RequestAbilitiesMapping();
}

bool APSPlayerController::RequestSquadAbilitiesMappingServer_Validate(APSSquad* Squad)
{
	return true;
}

void APSPlayerController::ReceivedSquadAbilitiesMappingSetClient_Implementation(APSSquad* Squad, EAbilityType NewAbilityType, FAbilityMappingSet NewAbilityMappingSet)
{
	Squad->ReceivedAbilitiesMappingSet(NewAbilityType, NewAbilityMappingSet);
}

void APSPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APSPlayerController, SelectedSquads);
	DOREPLIFETIME(APSPlayerController, Team);
}
