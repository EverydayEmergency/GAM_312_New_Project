// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_312_New_ProjectGameMode.h"
#include "GAM_312_New_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGAM_312_New_ProjectGameMode::AGAM_312_New_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
