// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PSTypes.h"
#include "PSGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	/** Indicates whether this ability has to be executed in place or checking the distance against a given target. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ExecuteInPlace = false;

	/** Maximum distance to which this ability can be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UseDistance;

	/** Indicates whether we want this ability to set Unit->CurrentAbility to nullptr when finished or canceled. True by default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCancelItself = true;

	/** Weapon data to equip to the unit in case this ability gets equipped on the EAbilityType::ActionEnemyUnit slot. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponData* WeaponData;

	UPROPERTY(BlueprintReadOnly)
	class APSUnit* UnitOwner;

	UPROPERTY(BlueprintReadOnly)
	class APSUnitController* ControllerOwner;

	UFUNCTION(BlueprintPure)
	bool IsAbilityActive() const;

protected:

	// Begin GameplayAbility interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End GameplayAbility interface
	
};
