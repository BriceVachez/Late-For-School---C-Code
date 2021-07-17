// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_test_5GameMode.h"
#include "FPS_test_5Character.h"
#include "UObject/ConstructorHelpers.h"

AFPS_test_5GameMode::AFPS_test_5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
