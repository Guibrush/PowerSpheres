// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSFormationComponent.h"
#include "PSFormation.generated.h"

UCLASS()
class POWERSPHERES_API APSFormation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSFormation();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<UPSFormationComponent*> FormationPositions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
