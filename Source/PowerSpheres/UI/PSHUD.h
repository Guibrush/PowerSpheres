// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Units/PSUnit.h"
#include "PSHUD.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API APSHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

	void StartSelectionRectangle();

	const TArray<APSUnit*> FinishSelectionRectangle();

	UFUNCTION(BlueprintCallable)
	const TArray<APSUnit*> GetTempSelectedUnits();

private:

	void GetUnitsInSelectionRectangle(const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<APSUnit*>& OutActors);

	bool bDoSelectionRetancle = false;

	FVector2D InitialMousePos;
	FVector2D FinalMousePos;

	TArray<APSUnit*> SelectedUnits;
	
};
