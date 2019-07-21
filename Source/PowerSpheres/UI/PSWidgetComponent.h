// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PSWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class POWERSPHERES_API UPSWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	UPSWidgetComponent();

	virtual void InitWidget() override;

};
