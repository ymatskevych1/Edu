// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "UObject/Object.h"
#include "EduFallingDamageComponent.generated.h"

class UMovementComponent;
class UEduHealthComponent;
UCLASS()
class EDUPROJECT_API UEduFallingDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Initialize(UEduHealthComponent* InHealthComponent, UMovementComponent* InMovementComponent);

	void ShouldTrackFalling(bool InbShouldTrack);
	void CalculateFalling();
				
private:

	UPROPERTY()
	UMovementComponent* MovementComponent;
	UPROPERTY()
	UEduHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float fMinFallingSpeedForDamage = 100.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.01", ClampMax = "1"))
	float fDamageCoefficient = 0.3f;

	bool bShouldTrack = false;
	float fLastFallingSpeed = 0.f;
};
