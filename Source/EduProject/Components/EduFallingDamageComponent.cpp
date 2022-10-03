// Fill out your copyright notice in the Description page of Project Settings.


#include "EduFallingDamageComponent.h"

#include "EduHealthComponent.h"

void UEduFallingDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bShouldTrack)
	{
		return;
	}

	fLastFallingSpeed = MovementComponent->Velocity.Z;
}

void UEduFallingDamageComponent::Initialize(UEduHealthComponent* InHealthComponent, UMovementComponent* InMovementComponent)
{
	if (!IsValid(InHealthComponent))
	{
		ensureMsgf(false, TEXT("[UEduFallingDamageComponent]: Trying to initialize with invalid HealthComponent"));
	}

	if (!IsValid(InMovementComponent))
	{
		ensureMsgf(false, TEXT("[UEduFallingDamageComponent]: Trying to initialize with invalid MovementComponent"));
	}
	
	HealthComponent = InHealthComponent;
	MovementComponent = InMovementComponent;
}

void UEduFallingDamageComponent::ShouldTrackFalling(bool InbShouldTrack)
{
	bShouldTrack = InbShouldTrack;
}

void UEduFallingDamageComponent::CalculateFalling()
{
	bShouldTrack = false;

	const float AbsoluteSpeed = FMath::Abs(fLastFallingSpeed); 
	if (AbsoluteSpeed > fMinFallingSpeedForDamage)
	{
		HealthComponent->DealDamage(AbsoluteSpeed * fDamageCoefficient);
	}
}
