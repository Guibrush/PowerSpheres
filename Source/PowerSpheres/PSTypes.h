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
