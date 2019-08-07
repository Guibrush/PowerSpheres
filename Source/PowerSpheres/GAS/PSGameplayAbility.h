// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PSGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class POWERSPHERES_API UPSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	/** Maximum distance to which this ability can be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UseDistance;

	/** Indicates whether we want this ability to set Unit->CurrentAbility to nullptr when finished or canceled. True by default. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCancelItself = true;

	/** Weapon to equip to the unit in case this ability gets equipped on the EAbilityType::ActionEnemyUnit slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* AbilityWeapon;

	UPROPERTY(BlueprintReadOnly)
	class APSUnit* UnitOwner;

	UPROPERTY(BlueprintReadOnly)
	class APSUnitController* ControllerOwner;

protected:

	// Begin GameplayAbility interface
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End GameplayAbility interface
	
};
