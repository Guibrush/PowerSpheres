// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSPowerSphereCrate.generated.h"

UCLASS()
class POWERSPHERES_API APSPowerSphereCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APSPowerSphereCrate();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "PowerSphereCrate")
	bool IsOpened = false;

public:

	UFUNCTION(BlueprintNativeEvent, Category = "PowerSphereCrate")
	bool TryToOpen();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PowerSphereCrate")
	void SpawnPowerSpheres();

	UFUNCTION(BlueprintCallable, Category = "PowerSphereCrate")
	bool GetIsOpened() const { return IsOpened; }
};
