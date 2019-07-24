// Copyright 2019-2020 Alberto & co. All Rights Reserved.

#include "PSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "MapViewComponent.h"

APSCharacter::APSCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(0.f, 0.f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->Deactivate();

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	//if (DecalMaterialAsset.Succeeded())
	//{
	//	CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	//}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	MapView = CreateDefaultSubobject<UMapViewComponent>(TEXT("MapView"));
	MapView->SetupAttachment(RootComponent);

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	MovementInputVector = FVector::ZeroVector;
}

void APSCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	if (!MovementInputVector.IsNearlyZero(1.0f))
	{
		MovementInputVector.Z = 0.f;

		FVector NewPosition = GetActorLocation() + MovementInputVector * DeltaSeconds * CameraMovementSpeed;
		SetActorLocation(NewPosition);

		MovementInputVector = FMath::Lerp<FVector>(MovementInputVector, FVector::ZeroVector, DeltaSeconds * CameraRecoverySpeed);
	}

	if (!FMath::IsNearlyZero(ZoomInput, 0.1f))
	{
		CameraBoom->TargetArmLength += ZoomInput * CameraZoomSpeed;
		CameraBoom->TargetArmLength = FMath::Clamp<float>(CameraBoom->TargetArmLength, CameraZoomCloseLimit, CameraZoomFarLimit);

		ZoomInput = FMath::Lerp(ZoomInput, 0.f, DeltaSeconds * CameraZoomRecoverySpeed);
	}
}

void APSCharacter::MoveForward(float Val)
{
	MovementInputVector += TopDownCameraComponent->GetUpVector() * Val;
}

void APSCharacter::MoveRight(float Val)
{
	MovementInputVector += TopDownCameraComponent->GetRightVector() * Val;
}

void APSCharacter::ZoomIn(float Val)
{
	ZoomInput += Val;
}

void APSCharacter::BeginPlay()
{
	Super::BeginPlay();

	CursorToWorld->SetDecalMaterial(CursorToWorldMaterial);
}
