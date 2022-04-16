// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestingGroundGameMode.h"
#include "TestingGroundHUD.h"
#include "TestingGroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGroundGameMode::ATestingGroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundHUD::StaticClass();
}
