// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EduHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EDUPROJECT_API UEduHealthComponent : public UActorComponent
{
	GENERATED_BODY()


public:

	void DealDamage(float InDamage);
};
