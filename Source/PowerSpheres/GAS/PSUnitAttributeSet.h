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

	/** Hitpoints. Self-explanatory. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData Health;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetHealthAttribute() const;

	/** This needs to be an attribute due to how the attributes work on GAS. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxHealth;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetMaxHealthAttribute();

	/** Movement speed of this unit. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData Movement;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetMovementAttribute();

	/** Attack value of this unit. It will be used to deal damage. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData Attack;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetAttackAttribute();

	/** Physical defence of this unit. It will be compared with Attack. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData Defence;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetDefenceAttribute();

	/** Defence against elemental effects. */
	UPROPERTY(BlueprintReadOnly, Replicated)
	FGameplayAttributeData ElementalDefence;

	/** Gets the actual attribute to allow further calculation with it. */
	UFUNCTION(BlueprintCallable)
	FGameplayAttribute GetElementalDefenceAttribute();

	// Begin AttributeSet interface
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	// End AttributeSet interface
	
};
