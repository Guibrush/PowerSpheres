// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PSUnitAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSUnitAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Hitpoints. Self-explanatory.
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth;

	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetHealthAttribute();

	// Begin AttributeSet interface
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	// End AttributeSet interface
	
};
