// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EduProjectCharacter.generated.h"

UCLASS(config=Game)
class AEduProjectCharacter : public ACharacter
{
	GENERATED_BODY()
#pragma region UE_Template
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UEduHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AEduProjectCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
#pragma endregion

public:

	virtual void BeginPlay() override;
	
private:

	UFUNCTION()
	virtual void OnCharacterLanded(const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Fall Damage", meta = (ClampMin = 0.f))
	float MinSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = "Fall Damage", meta = (ClampMin = 0.01f, ClampMax = 1.f))
	float DamageCoefficient = 1.f;
};

