// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSUnit.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/DecalComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Squads/PSSquad.h"
#include "Player/PSPlayerController.h"
#include "MapRevealerComponent.h"
#include "MapIconComponent.h"
#include "Engine/World.h"

// Sets default values
APSUnit::APSUnit()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Our map revealer component.
	MapRevealer = CreateDefaultSubobject<UMapRevealerComponent>(TEXT("MapRevealer"));
	MapRevealer->SetupAttachment(RootComponent);

	// Our map icon component.
	MapIcon = CreateDefaultSubobject<UMapIconComponent>(TEXT("MapIcon"));
	MapIcon->SetupAttachment(RootComponent);

	// Our ability system component.
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	CurrentAbility = nullptr;
}

// Called when the game starts or when spawned
void APSUnit::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		Squad = Cast<APSSquad>(GetOwner());
	}

	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);

		if (AttrDataTable && AttributeSetBlueprint)
		{
			AttributeSet = AbilitySystem->InitStats(AttributeSetBlueprint, AttrDataTable);
		}
	}

	if (const UPSUnitAttributeSet* PSAttributeSet = Cast<UPSUnitAttributeSet>(AttributeSet))
	{
		float MovementSpeed = PSAttributeSet->GetMovementAttribute().GetNumericValue(AttributeSet);
		GetCharacterMovement()->MaxWalkSpeed *= MovementSpeed;
		GetCharacterMovement()->MaxAcceleration *= MovementSpeed;

		float VisionRadius = PSAttributeSet->GetVisionRadiusAttribute().GetNumericValue(AttributeSet);
		MapRevealer->SetBoxExtent(FVector(VisionRadius, VisionRadius, 0.0f));
	}

	if (MapIcon)
	{
		MapIcon->OnIconEnteredView.AddDynamic(this, &APSUnit::OnUnitLeftFOW);
		MapIcon->OnIconLeftView.AddDynamic(this, &APSUnit::OnUnitEnteredFOW);
	}

	CheckInitMapComponents();
}

void APSUnit::CheckInitMapComponents()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		APSPlayerController* PSController = Cast<APSPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		if (PSController)
		{
			if (MapRevealer && PSController->Team != Team)
			{
				MapRevealer->DestroyComponent();
			}

			InitMapComponents();
		}
		else
		{
			// Little hack to fix a unknown bug about not getting the proper PSPlayerController on BeginPlay.
			World->GetTimerManager().SetTimerForNextTick(this, &APSUnit::CheckInitMapComponents);
		}
	}
}

// Called every frame
void APSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APSUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APSUnit::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APSUnit, Squad);
	DOREPLIFETIME(APSUnit, CurrentAbilityParams);
	DOREPLIFETIME(APSUnit, Team);
	DOREPLIFETIME(APSUnit, PlayerOwner);
	DOREPLIFETIME(APSUnit, CurrentAbility);
	DOREPLIFETIME(APSUnit, ActionMoveToLocation);
}

void APSUnit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();
}

void APSUnit::UnitSelectedClient_Implementation()
{
	SetSelectionDecalVisibility(true);
}

void APSUnit::UnitDeselectedClient_Implementation()
{
	SetSelectionDecalVisibility(false);
}

void APSUnit::GiveAbility(TSubclassOf<class UPSGameplayAbility> Ability)
{
	if (AbilitySystem)
	{
		if (HasAuthority() && Ability)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.Get(), 1, 0));
		}
	}
}

void APSUnit::UseAbility(TSubclassOf<class UPSGameplayAbility> Ability, bool bIsUserInput)
{
	if (HasAuthority() && AbilitySystem && Ability)
	{
		if (bIsUserInput)
		{
			if (CurrentAbility)
			{
				UAIBlueprintHelperLibrary::SendAIMessage(this, "EndAbility", this, true);
			}

			CurrentAbility = Ability;
		}
		else
		{
			AbilitySystem->TryActivateAbilityByClass(Ability.Get());
		}
	}
}

void APSUnit::Die(APSUnit* Attacker)
{
	if (HasAuthority() && Squad && Attacker)
	{
		Squad->UnitDied(this);

		Destroy();
	}
}

void APSUnit::TargetDied(APSUnit* Target)
{
	if (HasAuthority() && Target)
	{
		APSUnit* TargetUnit = Cast<APSUnit>(Target);
		if (TargetUnit && TargetUnit->Squad == CurrentAbilityParams.Actor && TargetUnit->Squad->SquadDestroyed())
		{
			if (CurrentAbility)
			{
				UGameplayAbility* AbilityCDO = Cast<UGameplayAbility>(CurrentAbility.GetDefaultObject());
				AbilitySystem->CancelAbility(AbilityCDO);
			}

			CurrentAbility = nullptr;

			if (Squad)
			{
				Squad->TargetSquadDestroyed(TargetUnit->Squad);
			}
		}
	}
}

void APSUnit::TargetSquadDestroyed(APSSquad* TargetSquad)
{
	if (HasAuthority() && TargetSquad && TargetSquad == CurrentAbilityParams.Actor)
	{
		if (CurrentAbility)
		{
			UGameplayAbility* AbilityCDO = Cast<UGameplayAbility>(CurrentAbility.GetDefaultObject());
			AbilitySystem->CancelAbility(AbilityCDO);
		}

		CurrentAbility = nullptr;
	}
}

bool APSUnit::IsAlive()
{
	if (const UPSUnitAttributeSet* PSAttributeSet = Cast<UPSUnitAttributeSet>(AttributeSet))
	{
		float Health = PSAttributeSet->GetHealthAttribute().GetNumericValue(AttributeSet);
		return Health > 0.0f;
	}

	return false;
}

void APSUnit::SetSelectionDecalVisibility(bool NewVisibility)
{
	TArray<UDecalComponent*> DecalComponents;
	GetComponents<UDecalComponent>(DecalComponents);
	for (UDecalComponent* Decal : DecalComponents)
	{
		Decal->SetVisibility(NewVisibility);
	}
}

void APSUnit::OnUnitLeftFOW(UMapIconComponent* MapIconComp, UMapViewComponent* MapViewComp)
{
	CoveredByFOW = false;

	UnitLeftFOW();
}

void APSUnit::OnUnitEnteredFOW(UMapIconComponent* MapIconComp, UMapViewComponent* MapViewComp)
{
	CoveredByFOW = true;

	UnitEnteredFOW();
}
