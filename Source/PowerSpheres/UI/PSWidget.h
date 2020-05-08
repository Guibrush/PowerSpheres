// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IUserObjectListEntry.h"
#include "PSWidget.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	/* Set the owning actor so widgets have access to whatever is, broadcasting OnOwningActorChanged event */
	UFUNCTION(BlueprintCallable)
	void SetOwningActor(AActor* NewOwner);

protected:

	/* Actor that widget is attached to via WidgetComponent */
	UPROPERTY(BlueprintReadOnly, Category = "ActorWidget")
	AActor* OwningActor;

};
