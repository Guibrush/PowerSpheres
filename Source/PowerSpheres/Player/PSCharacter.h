// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSTypes.h"
#include "PSCharacter.generated.h"

UCLASS(Blueprintable)
class APSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Moves this character forward which results in an "up" camera movement from the player point of view */
	void MoveForward(float Val);
	/** Moves this character to the right which results in a "right" camera movement from the player point of view */
	void MoveRight(float Val);
	/** Moves the camera closer or far away from the battlefield. */
	void ZoomIn(float Val);

	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	//~ End AActor Interface.

	/** Speed of movement of this character which at the end is the movement speed of the camera. */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraMovementSpeed = 1.0f;

	/** Speed used to decrease the input movement of this character which is the camera from the point of view of the player. */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraRecoverySpeed = 1.0f;

	/** Speed of the zoom. */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraZoomSpeed = 1.0f;

	/** Speed used to decrease the input of the zoom. */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraZoomRecoverySpeed = 1.0f;

	/** Close limit for the zoom (camera spring distance) */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraZoomCloseLimit = 0.0f;

	/** Far limit for the zoom (camera spring distance) */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	float CameraZoomFarLimit = 1000.0f;

	/** Decal to project to the ground to indicate the position of the cursor. */
	UPROPERTY(EditAnywhere, Category = "Camera Settings")
	class UMaterialInterface* CursorToWorldMaterial;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/** Component to show the area around the player camera on the minimap. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap, meta = (AllowPrivateAccess = "true"))
	class UMapViewComponent* MapView;

	/** Internal vector to accumulate the movement input of the player. */
	FVector MovementInputVector;

	/** Internal value to accumulate the zoom input of the player. */
	float ZoomInput;
};

