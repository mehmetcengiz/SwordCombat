// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStates/CharacterState.h"
#include "InteractState.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWORDCOMBAT_API UInteractState : public UCharacterState
{
	GENERATED_BODY()

public:
	
	void OnRightButtonPressed() override;
	
	
};
