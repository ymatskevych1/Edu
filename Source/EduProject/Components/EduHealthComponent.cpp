// Fill out your copyright notice in the Description page of Project Settings.


#include "EduHealthComponent.h"

void UEduHealthComponent::DealDamage(float InDamage)
{
	const FString Message = FString::Printf(TEXT("%f damage taken"), InDamage);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Message);
}
