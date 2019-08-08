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
		, UnitAbilities(TMap<EAbilityType, TSubclassOf<class UPSGameplayAbility>>())
	{ }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class APSUnit> UnitBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAbilityType, TSubclassOf<class UPSGameplayAbility>> UnitAbilities;
};
