// Copyright Epic Games, Inc. All Rights Reserved.

#include "EduProjectGameMode.h"
#include "EduProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEduProjectGameMode::AEduProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
