// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GAS/PSUnitAttributeSet.h"
#include "PSTypes.h"
#include "PSUnit.generated.h"

UCLASS()
class POWERSPHERES_API APSUnit : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APSUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PossessedBy(AController* NewController) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};

	const UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	};

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	//TSubclassOf<class UGameplayAbility> Ability;

	/** This function gets called only on the client who selected this unit. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void UnitSelectedClient();

	/** This function gets called only on the client who deselected this unit. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void UnitDeselectedClient();

	void GiveAbility(TSubclassOf<class UPSGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable)
	void UseAbility(TSubclassOf<class UPSGameplayAbility> Ability, bool bIsUserInput);

	UFUNCTION()
	void Die(APSUnit* Attacker);

	UFUNCTION()
	void TargetDied(APSUnit* Target);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	UDataTable* AttrDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TSubclassOf<UPSUnitAttributeSet> AttributeSetBlueprint;

	UPROPERTY(BlueprintReadOnly, Replicated)
	class APSSquad* Squad;

	UPROPERTY(BlueprintReadOnly, Replicated)
	ETeamType Team;

	UPROPERTY(BlueprintReadOnly, Replicated)
	class APSPlayerController* PlayerOwner;

	UPROPERTY(BlueprintReadOnly, Replicated)
	FAbilityParams CurrentAbilityParams;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FVector ActionMoveToLocation;

	UPROPERTY(BlueprintReadOnly, Replicated)
	TSubclassOf<class UPSGameplayAbility> CurrentAbility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSelectionDecalVisibility(bool NewVisibility);

private:

	/** Our ability system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	/** Our attribute set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	const class UAttributeSet* AttributeSet;

};
