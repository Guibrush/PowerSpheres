// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GAS/PSUnitAttributeSet.h"
#include "PSTypes.h"
#include "PSMeshMergeFunctionLibrary.h"
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

	class UMapRevealerComponent* GetMapRevealer() const
	{
		return MapRevealer;
	};

	/** This function gets called only on the client who selected this unit. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void UnitSelectedClient();

	/** This function gets called only on the client who deselected this unit. Is meant to deal with the UI and other client feedback. */
	UFUNCTION(Client, Unreliable)
	void UnitDeselectedClient();

	void GiveAbilities(TMap<EAbilityType, TSubclassOf<class UPSGameplayAbility>> Abilities);

	UFUNCTION(BlueprintCallable)
	void UseAbility(EAbilityType AbilityType, bool bIsUserInput);

	UFUNCTION()
	void Die(APSUnit* Attacker);

	UFUNCTION()
	void TargetDied(APSUnit* Target);

	UFUNCTION()
	void TargetSquadDestroyed(APSSquad* TargetSquad);

	// TODO: This is part of the nasty hack that we are doing on the Tick. When the hack is fixed we need to reevaluate if we need this
	// function at all.
	UFUNCTION(BlueprintImplementableEvent)
	void InitMapComponents();

	UFUNCTION(BlueprintImplementableEvent)
	void UnitLeftFOW();

	UFUNCTION(BlueprintImplementableEvent)
	void UnitEnteredFOW();

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class UPSGameplayAbility> GetCurrentAbility();

	/**
	Function executed from the server's player controller who owns this unit. This function will iterate over
	the abilities calling a client function on the player controller to receive the data.
	*/
	UFUNCTION()
	void RequestAbilities();

	/**
	This function will be called only on the client's player controller who owns this unit. This function
	will introduce the new entry in the client's map.
	*/
	UFUNCTION()
	void ReceivedAbility(EAbilityType NewAbilityType, TSubclassOf<class UPSGameplayAbility> NewAbility);

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

	UPROPERTY(BlueprintReadWrite, Replicated)
	FAbilityParams CurrentAbilityParams;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FVector ActionMoveToLocation;

	UPROPERTY(BlueprintReadOnly, Replicated)
	EAbilityType CurrentAbilityType;

	/** Indicates whether this unit is covered in fog for this client or not. */
	UPROPERTY(BlueprintReadOnly)
	bool CoveredByFOW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PSMesh, Replicated)
	FPSSkeletalMeshMergeParams MeshMergeParameters;

	UPROPERTY(BlueprintReadOnly)
	TMap<EAbilityType, TSubclassOf<class UPSGameplayAbility>> UnitAbilities;

	UPROPERTY(BlueprintReadOnly, Replicated)
	UWeaponData* EquippedWeaponData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSelectionDecalVisibility(bool NewVisibility);

	// Called when this unit is revealed from fog of war.
	UFUNCTION()
	void OnUnitLeftFOW(class UMapIconComponent* MapIconComp, class UMapViewComponent* MapViewComp);

	//  Called when this unit becomes hidden because it enters in the fog of war.
	UFUNCTION()
	void OnUnitEnteredFOW(class UMapIconComponent* MapIconComp, class UMapViewComponent* MapViewComp);

private:

	/** Component to reveal the FOW around this actor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap, meta = (AllowPrivateAccess = "true"))
	class UMapRevealerComponent* MapRevealer;

	/** Component to have an ico in the minimap representing this actor. Also to be hidden from FOW. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap, meta = (AllowPrivateAccess = "true"))
	class UMapIconComponent* MapIcon;

	/** Our ability system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	/** Our attribute set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	const class UAttributeSet* AttributeSet;

	// Helper function to check when the game starts the initialization of the map components.
	// It calls itself every tick if the PSPlayerController is not valid until is valid.
	void CheckInitMapComponents();

	void GiveAbility(TSubclassOf<class UPSGameplayAbility> Ability);

};
