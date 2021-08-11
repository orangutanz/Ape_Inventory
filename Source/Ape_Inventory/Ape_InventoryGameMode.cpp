// Copyright Epic Games, Inc. All Rights Reserved.

#include "Ape_InventoryGameMode.h"
#include "Ape_InventoryPlayerController.h"
#include "Ape_InventoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AApe_InventoryGameMode::AApe_InventoryGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AApe_InventoryPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}