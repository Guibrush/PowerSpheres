// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PSTypes.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None = 0,
	ActionMoveTo = 1,
	ActionEnemyUnit = 2,
	ActionFriendlyUnit = 3,
	ActionNeutralUnit = 4,
	Ability1 = 5,
	Ability2 = 6,
	Ability3 = 7,
	Ability4 = 8,
	Ability5 = 9,
	Ability6 = 10,
	Ability7 = 11,
	Ability8 = 12,
	Ability9 = 13,
	Ability10 = 14,
	MAX,
};

UENUM(BlueprintType)
enum class ETeamType : uint8
{
	NoTeam = 0,
	AI = 1,
	Team1 = 2,
	Team2 = 3,
	Team3 = 4,
	Team4 = 5,
	Neutral,
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
struct POWERSPHERES_API FSquadEquipment
{
	GENERATED_USTRUCT_BODY()

	FSquadEquipment()
		: AbilitiesSlots(TMap<EAbilityType, TSubclassOf<class UPSPowerSphereData>>())
		, Effects(TArray<TSubclassOf<class UPSPowerSphereData>>())
	{ }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAbilityType, TSubclassOf<class UPSPowerSphereData>> AbilitiesSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class UPSPowerSphereData>> Effects;
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
		, DieAnim(nullptr)
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimSequenceBase* DieAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* AbilityWeapon;
};
