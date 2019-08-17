// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PSTypes.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None,
	ActionMoveTo,
	ActionEnemyUnit,
	ActionFriendlyUnit,
	ActionNeutralUnit,
	Ability1,
	Ability2,
	Ability3,
	Ability4,
	Ability5,
	Ability6,
	Ability7,
	Ability8,
	Ability9,
	Ability10,
	MAX,
};

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	NoTeam = 0,
	Team1 = 1,
	Team2 = 2,
	Team3 = 3,
	Neutral,
};

UENUM(BlueprintType)
enum class EPowerSphereType : uint8
{
	None,
	Generic,
	ActionMoveTo,
	ActionEnemyUnit,
};

USTRUCT(BlueprintType)
struct POWERSPHERES_API FAbilityParams
{
	GENERATED_USTRUCT_BODY()

	FAbilityParams()
		: Position(FVector::ZeroVector)
		, Direction(FVector::ZeroVector)
		, Rotation(FRotator::ZeroRotator)
		, Actor(nullptr)
		, AISelectedTarget(nullptr)
	{ }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* AISelectedTarget;
};

USTRUCT(BlueprintType)
struct POWERSPHERES_API FUnitComposition
{
	GENERATED_USTRUCT_BODY()

	FUnitComposition()
		: UnitBlueprint(nullptr)
		, MovementSlot(nullptr)
		, WeaponSlot(nullptr)
		, AbilitiesPowerSpheres(TArray<TSubclassOf<class UPSPowerSphere>>())
		, bOverwriteSquadAbilities(false)
		, EffectsPowerSpheres(TArray<TSubclassOf<class UPSPowerSphere>>())
		, bOverwriteSquadEffects(false)
	{ }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class APSUnit> UnitBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UPSPowerSphere> MovementSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UPSPowerSphere> WeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UPSPowerSphere>> AbilitiesPowerSpheres;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bOverwriteSquadAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UPSPowerSphere>> EffectsPowerSpheres;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bOverwriteSquadEffects;
};

UCLASS(BlueprintType)
class POWERSPHERES_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:

	UWeaponData()
		: IdleAnim(nullptr)
		, IdleBreakAnim(nullptr)
		, RunAnim(nullptr)
		, ShootAnim(nullptr)
		, ShootIdleAnim(nullptr)
		, ReloadAnim(nullptr)
		, AbilityWeapon(nullptr)
	{ }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* IdleAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* IdleBreakAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* RunAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* ShootAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* ShootIdleAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* ReloadAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* AbilityWeapon;
};
