// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSAggroComponent.generated.h"

USTRUCT(BlueprintType)
struct POWERSPHERES_API FAggroPawnTimer
{
	GENERATED_USTRUCT_BODY()

	FAggroPawnTimer()
		: AggroPawn(nullptr)
		, CurrentAggro(0.0f)
		, TimeOut(0.0f)
	{ }

	UPROPERTY(BlueprintReadOnly)
	APawn* AggroPawn;

	UPROPERTY(BlueprintReadOnly)
	float CurrentAggro;

	UPROPERTY(BlueprintReadOnly)
	float TimeOut;

	bool operator==(const FAggroPawnTimer& OtherAggroPawnTimer) const
	{
		return AggroPawn == OtherAggroPawnTimer.AggroPawn;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POWERSPHERES_API UPSAggroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UPSAggroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Aggro table. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FAggroPawnTimer> AggroPawns;

	/** Aggro decrease rate per second. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AggroDecreaseRate = 1.0f;

	/** Aggro increase rate per action (getting damage, seeing the enemy, etc). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AggroIncreaseRate = 2.0f;

	/** Time (in seconds) for a pawn to disappear from the aggro list when reaches zero aggro. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeOutAtZeroAggro = 2.0f;

	/**
		Inserts a new aggro pawn with the base aggro increase rate multiplied by the BaseAggroFactor parameter.
		If the pawn already exists it resets the aggro to the base amount previously calculated only if its lower 
		than that value.
	*/
	UFUNCTION(BlueprintCallable)
	void NewAggroPawn(APawn* AggroPawn, float BaseAggroFactor=1.0f);

	/**
		Increases the aggro for a given pawn by the rate setted in the component multiplied by an optional factor.
		If the pawn wasn't in the list previously it creates a new entry.
	*/
	UFUNCTION(BlueprintCallable)
	void IncreaseAggroForPawn(APawn* AggroPawn, float MultFactor=1.0f);

	/**
		Decreases the aggro for a give pawn by the amount indicated. This can trigger the time out to eliminate a pawn
		from the list.
	*/
	UFUNCTION(BlueprintCallable)
	void DecreaseAggroForPawn(APawn* AggroPawn, float DecreaseAmount);

	/** It returns the highest entry in the aggro list updated every tick. */
	UFUNCTION(BlueprintCallable)
	FAggroPawnTimer GetHighestAggroPawn();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	/** Index of the highest aggro pawn in the list. This is updated every tick. */
	int32 HighestAggroPawnIndex;


};
