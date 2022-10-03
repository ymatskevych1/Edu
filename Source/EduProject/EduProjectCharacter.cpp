// Copyright Epic Games, Inc. All Rights Reserved.

#include "EduProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/EduFallingDamageComponent.h"
#include "Components/EduHealthComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#pragma region UE_Template

AEduProjectCharacter::AEduProjectCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	TurnRateGamepad = 50.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	FallingDamageComponent = CreateDefaultSubobject<UEduFallingDamageComponent>(TEXT("FallingDamageComponent"));
	FallingDamageComponent->PrimaryComponentTick.bCanEverTick = true;
	
	HealthComponent = CreateDefaultSubobject<UEduHealthComponent>(TEXT("HealthComponent"));
	
}

void AEduProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AEduProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AEduProjectCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AEduProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AEduProjectCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AEduProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AEduProjectCharacter::TouchStopped);
}

void AEduProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AEduProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AEduProjectCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AEduProjectCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AEduProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEduProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion UE_Template

void AEduProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	FallingDamageComponent->Initialize(HealthComponent, GetMovementComponent());
}

void AEduProjectCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	auto* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (!IsValid(MovementComponent))
	{
		ensureMsgf(false, TEXT("[AEduProjectCharacter]: MovementComponent is invalid"));
		return;
	}

	if (PrevMovementMode == EMovementMode::MOVE_Falling)
	{
		FallingDamageComponent->CalculateFalling();
	}
	
	switch (MovementComponent->MovementMode)
	{
	case EMovementMode::MOVE_Falling:
		{
			FallingDamageComponent->ShouldTrackFalling(true);
			break;
		}
	default:
		{
			FallingDamageComponent->ShouldTrackFalling(false);
		}
	}
}
