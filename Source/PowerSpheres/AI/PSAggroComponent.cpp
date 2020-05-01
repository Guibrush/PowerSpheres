// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSAggroComponent.h"

// Sets default values for this component's properties
UPSAggroComponent::UPSAggroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AggroPawns = TArray<FAggroPawnTimer>();
}

// Called when the game starts
void UPSAggroComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UPSAggroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float NewHighestAggro = 0.0f;
	int32 NewHighestAggroPawnIndex = 0;
	TArray<FAggroPawnTimer> AggroPawnsToDelete;
	for (int32 i = 0; i < AggroPawns.Num(); i++)
	{
		if (AggroPawns[i].CurrentAggro == 0.0f)
		{
			// If the current aggro is zero it means that this pawn is timing out to
			// be removed from the list.
			AggroPawns[i].TimeOut -= DeltaTime;
			AggroPawns[i].TimeOut = FMath::Max(AggroPawns[i].TimeOut, 0.0f);

			if (AggroPawns[i].TimeOut == 0.0f)
			{
				// If the pawn has timed out we marked to remove it later.
				AggroPawnsToDelete.Add(AggroPawns[i]);
			}
		}
		else
		{
			// If the current aggro is greater than zero we have to decrease the aggro.
			AggroPawns[i].CurrentAggro -= DeltaTime * AggroDecreaseRate;
			AggroPawns[i].CurrentAggro = FMath::Max(AggroPawns[i].CurrentAggro, 0.0f);
			if (AggroPawns[i].CurrentAggro == 0.0f)
			{
				// We check if the aggro has reached zero to start the time out timer.
				AggroPawns[i].TimeOut = TimeOutAtZeroAggro;
			}
		}

		// We update the highest aggro pawn to have that reference at the end of the loop.
		if (AggroPawns[i].CurrentAggro >= NewHighestAggro)
		{
			NewHighestAggro = AggroPawns[i].CurrentAggro;
			NewHighestAggroPawnIndex = i;
		}
	}

	HighestAggroPawnIndex = NewHighestAggroPawnIndex;

	// Finally we remove the pawns previously marked to be removed.
	for (FAggroPawnTimer AggroPawnToDelete : AggroPawnsToDelete)
	{
		AggroPawns.Remove(AggroPawnToDelete);
	}
}

void UPSAggroComponent::NewAggroPawn(APawn* AggroPawn, float BaseAggroFactor)
{
	FAggroPawnTimer NewAggroPawn = FAggroPawnTimer();
	NewAggroPawn.AggroPawn = AggroPawn;
	float BaseAggro = AggroIncreaseRate * BaseAggroFactor;

	int32 PawnIndex = AggroPawns.Find(NewAggroPawn);
	if (PawnIndex == INDEX_NONE)
	{
		NewAggroPawn.CurrentAggro = BaseAggro;
		AggroPawns.Add(NewAggroPawn);
	}
	else
	{
		AggroPawns[PawnIndex].CurrentAggro = FMath::Max(BaseAggro, AggroPawns[PawnIndex].CurrentAggro);
	}
}

void UPSAggroComponent::IncreaseAggroForPawn(APawn* AggroPawn, float MultFactor)
{
	FAggroPawnTimer NewAggroPawn = FAggroPawnTimer();
	NewAggroPawn.AggroPawn = AggroPawn;

	int32 PawnIndex = AggroPawns.Find(NewAggroPawn);
	if (PawnIndex == INDEX_NONE)
	{
		NewAggroPawn.CurrentAggro = AggroIncreaseRate * MultFactor;
		AggroPawns.Add(NewAggroPawn);
	}
	else
	{
		AggroPawns[PawnIndex].CurrentAggro += AggroIncreaseRate * MultFactor;
	}
}

void UPSAggroComponent::DecreaseAggroForPawn(APawn* AggroPawn, float DecreaseAmount)
{
	FAggroPawnTimer TempAggroPawn = FAggroPawnTimer();
	TempAggroPawn.AggroPawn = AggroPawn;

	int32 PawnIndex = AggroPawns.Find(TempAggroPawn);
	if ((PawnIndex != INDEX_NONE) && (AggroPawns[PawnIndex].CurrentAggro > 0.0f))
	{
		AggroPawns[PawnIndex].CurrentAggro -= DecreaseAmount;
		AggroPawns[PawnIndex].CurrentAggro = FMath::Max(AggroPawns[PawnIndex].CurrentAggro, 0.0f);
		if (AggroPawns[PawnIndex].CurrentAggro == 0.0f)
		{
			AggroPawns[PawnIndex].TimeOut = TimeOutAtZeroAggro;
		}
	}
}

FAggroPawnTimer UPSAggroComponent::GetHighestAggroPawn()
{
	FAggroPawnTimer ReturnAggroPawn = FAggroPawnTimer();
	if (AggroPawns.Num() > HighestAggroPawnIndex)
	{
		ReturnAggroPawn = AggroPawns[HighestAggroPawnIndex];
	}

	return ReturnAggroPawn;
}
