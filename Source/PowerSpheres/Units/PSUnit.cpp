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
#include "TimerManager.h"
#include "PowerSpheres/PSPowerSphere.h"
#include "PSStaticLibrary.h"

// Sets default values
APSUnit::APSUnit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	ResetCurrentAbility();
}

// Called when the game starts or when spawned
void APSUnit::BeginPlay()
{
	Super::BeginPlay();

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

	USkeletalMesh* MergedMesh = UPSMeshMergeFunctionLibrary::MergeMeshes(MeshMergeParameters);
	if (MergedMesh)
	{
		GetMesh()->SetSkeletalMesh(MergedMesh);
	}
}

void APSUnit::CheckInitMapComponents()
{
	UWorld* const World = GetWorld();
	if (!World)
	{
		return;
	}

	APSPlayerController* PSController = Cast<APSPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (PSController)
	{
		if (MapRevealer && UPSStaticLibrary::AreEnemyTeams(PSController->Team, Team))
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
	DOREPLIFETIME(APSUnit, CurrentAbilityType);
	DOREPLIFETIME(APSUnit, ActionMoveToLocation);
	DOREPLIFETIME(APSUnit, EquippedWeaponData);
	DOREPLIFETIME(APSUnit, MeshMergeParameters);
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

void APSUnit::GivePowers(TArray<TSubclassOf<class UPSPowerSphere>> PowerSpheres)
{
	for (TSubclassOf<class UPSPowerSphere> PowerSphere : PowerSpheres)
	{
		UPSPowerSphere* PowerSphereObject = PowerSphere.GetDefaultObject();
		if (PowerSphereObject)
		{
			GiveEffect(PowerSphereObject->GameplayEffect, 1.0f);
			GiveAbility(PowerSphereObject->GameplayAbility);
		}
	}
}

void APSUnit::GiveEffect(TSubclassOf<class UGameplayEffect> Effect, float Level)
{
	if (HasAuthority() && AbilitySystem && Effect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		UGameplayEffect* GameplayEffect = Effect->GetDefaultObject<UGameplayEffect>();
		AbilitySystem->ApplyGameplayEffectToSelf(GameplayEffect, Level, EffectContext);
	}
}

void APSUnit::GiveAbility(TSubclassOf<class UPSGameplayAbility> Ability)
{
	if (HasAuthority() && AbilitySystem && Ability)
	{
		AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.Get(), 1, 0));
	}
}

void APSUnit::UseAbility(EAbilityType AbilityType, bool bIsUserInput)
{
	if (HasAuthority() && Squad)
	{
		TSubclassOf<class UPSGameplayAbility>* Ability = Squad->AbilitiesMapping[AbilityType].UnitAbilityMap.Find(this);
		if (AbilitySystem && Ability)
		{
			if (bIsUserInput)
			{
				if (CurrentAbilityType != EAbilityType::None)
				{
					UGameplayAbility* AbilityCDO = Cast<UGameplayAbility>(Ability->GetDefaultObject());
					AbilitySystem->CancelAbility(AbilityCDO);
				}

				ResetCurrentAbility(false);

				// We wait one tick after setting CurrentAbilityType to None to let the AI to run
				// their logic.
				UWorld* const World = GetWorld();
				if (World)
				{
					FTimerDelegate TimerDelegate;
					TimerDelegate.BindUFunction(this, FName("SetCurrentAbilityType"), AbilityType);
					World->GetTimerManager().SetTimerForNextTick(TimerDelegate);
				}

			}
			else
			{
				AbilitySystem->TryActivateAbilityByClass(Ability->Get());
			}
		}
	}

	bLastUserInput = bIsUserInput;
}

void APSUnit::CancelCurrentAbility()
{
	if (CurrentAbilityType != EAbilityType::None)
	{
		TSubclassOf<class UPSGameplayAbility>* Ability = Squad->AbilitiesMapping[CurrentAbilityType].UnitAbilityMap.Find(this);
		if (Ability)
		{
			UGameplayAbility* AbilityCDO = Cast<UGameplayAbility>(Ability->GetDefaultObject());
			AbilitySystem->CancelAbility(AbilityCDO);
		}

		if (GetController())
		{
			GetController()->StopMovement();
		}
	}

	ResetCurrentAbility();
}

void APSUnit::SetCurrentAbilityType(EAbilityType NewAbilityType)
{
	CurrentAbilityType = NewAbilityType;
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
	if (HasAuthority() && Squad && Target)
	{
		APSUnit* TargetUnit = Cast<APSUnit>(Target);
		if (TargetUnit && TargetUnit->Squad == CurrentAbilityParams.Actor)
		{
			if (TargetUnit->Squad->SquadDestroyed())
			{
				Squad->TargetSquadDestroyed(TargetUnit->Squad);
			}
		}
	}
}

void APSUnit::TargetSquadDestroyed(APSSquad* TargetSquad)
{
	if (HasAuthority() && Squad && TargetSquad && TargetSquad == CurrentAbilityParams.Actor)
	{
		CancelCurrentAbility();
	}
}

void APSUnit::AbilityFinished(UPSGameplayAbility* Ability)
{
	if (HasAuthority() && Squad && CurrentAbilityType != EAbilityType::None)
	{
		TSubclassOf<class UPSGameplayAbility>* CurrentAbility = Squad->AbilitiesMapping[CurrentAbilityType].UnitAbilityMap.Find(this);
		if (CurrentAbility && *CurrentAbility == Ability->GetClass())
		{
			APSSquad* TargetSquad = Cast<APSSquad>(CurrentAbilityParams.Actor);
			if (!TargetSquad)
			{
				ResetCurrentAbility(true);
			}
			else if (TargetSquad->SquadDestroyed())
			{
				ResetCurrentAbility(true);
			}
			else if (bLastUserInput)
			{
				ResetCurrentAbility(false);
			}
		}
	}
}

void APSUnit::ResetCurrentAbility(bool ResetAbilityParams)
{
	CurrentAbilityType = EAbilityType::None;

	if (ResetAbilityParams)
		CurrentAbilityParams = FAbilityParams();
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

TSubclassOf<class UPSGameplayAbility> APSUnit::GetCurrentAbility()
{
	TSubclassOf<class UPSGameplayAbility> Ability = nullptr;
	if (CurrentAbilityType != EAbilityType::None)
	{
		Ability = Squad->AbilitiesMapping[CurrentAbilityType].UnitAbilityMap[this];
	}

	return Ability;
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
