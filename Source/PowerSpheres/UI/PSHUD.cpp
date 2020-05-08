// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSHUD.h"
#include "Player/PSPlayerController.h"
#include "PSTypes.h"
#include "EngineUtils.h"

void APSHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDoSelectionRetancle)
	{
		//APowerSpheresPlayerController* Controller = Cast<APowerSpheresPlayerController>(PlayerOwner);

		ULocalPlayer* LocalPlayer = GetOwningPlayerController() ? Cast<ULocalPlayer>(GetOwningPlayerController()->Player) : NULL;
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FVector2D MousePosition;
			if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			{
				FinalMousePos = MousePosition;
			}
		}

		if (FVector2D::Distance(InitialMousePos, FinalMousePos) > 10.0f)
		{
			FLinearColor RectColor = FLinearColor::Green;
			RectColor.A = 0.5f;
			DrawRect(RectColor, InitialMousePos.X, InitialMousePos.Y, FinalMousePos.X - InitialMousePos.X, FinalMousePos.Y - InitialMousePos.Y);

			GetUnitsInSelectionRectangle(InitialMousePos, FinalMousePos, SelectedUnits);
		}
	}
}

void APSHUD::StartSelectionRectangle()
{
	bDoSelectionRetancle = true;
	SelectedUnits.Empty();

	ULocalPlayer* LocalPlayer = GetOwningPlayerController() ? Cast<ULocalPlayer>(GetOwningPlayerController()->Player) : NULL;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			InitialMousePos = MousePosition;
		}
	}
}

const TArray<APSUnit*> APSHUD::FinishSelectionRectangle()
{
	bDoSelectionRetancle = false;

	TArray<APSUnit*> TempSelectedUnits = SelectedUnits;
	SelectedUnits.Empty();

	return TempSelectedUnits;
}

const TArray<APSUnit*> APSHUD::GetTempSelectedUnits()
{
	return SelectedUnits;
}

void APSHUD::GetUnitsInSelectionRectangle(const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<APSUnit*>& OutActors)
{
	APSPlayerController* PlayerController = Cast<APSPlayerController>(GetOwningPlayerController());
	if (!PlayerController)
	{
		return;
	}

	ETeamType PlayerTeam = PlayerController->Team;

	// Because this is a HUD function it is likely to get called each tick,
	// so make sure any previous contents of the out actor array have been cleared!
	OutActors.Reset();

	//Create Selection Rectangle from Points
	FBox2D SelectionRectangle(ForceInit);

	//This method ensures that an appropriate rectangle is generated, 
	//		no matter what the coordinates of first and second point actually are.
	SelectionRectangle += FirstPoint;
	SelectionRectangle += SecondPoint;

	for (TActorIterator<APSUnit> Itr(GetWorld()); Itr; ++Itr)
	{
		APSUnit* EachActor = *Itr;

		if (EachActor->Team != PlayerTeam || EachActor->PlayerOwner != PlayerController)
		{
			continue;
		}

		//Get Actor Bounds				//casting to base class, checked by template in the .h
		const FBox EachActorBounds = EachActor->GetComponentsBoundingBox(); /* All Components? */

		//Center
		const FVector BoxCenter = EachActorBounds.GetCenter();

		const FVector ProjectedWorldLocation = Project(BoxCenter);
		FVector2D ActorBox2D = FVector2D(ProjectedWorldLocation.X, ProjectedWorldLocation.Y);

		if (SelectionRectangle.IsInside(ActorBox2D))
		{
			OutActors.Add(EachActor);
		}
	}
}
