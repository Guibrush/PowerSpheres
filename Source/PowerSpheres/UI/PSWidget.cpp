// Copyright 2019-2020 Alberto & co. All Rights Reserved.


#include "PSWidget.h"

void UPSWidget::SetOwningActor(AActor* NewOwner)
{
	if (OwningActor == NewOwner)
	{
		// Skip repeated calls
		return;
	}

	OwningActor = NewOwner;
}