// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SwordCombatGameMode.h"
#include "SwordCombatCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASwordCombatGameMode::ASwordCombatGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/Blueprint/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
