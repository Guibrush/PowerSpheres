// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSWidgetComponent.h"
#include "PSWidget.h"

UPSWidgetComponent::UPSWidgetComponent()
{
	// Set common defaults when using widgets on Actors
	SetDrawAtDesiredSize(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void UPSWidgetComponent::InitWidget()
{
	// Base implementation creates the 'Widget' instance
	Super::InitWidget();

	UPSWidget* WidgetInst = Cast<UPSWidget>(Widget);
	if (WidgetInst)
	{
		// Assign the owner, now we have easy access in the widget itself
		WidgetInst->SetOwningActor(GetOwner());
	}
}