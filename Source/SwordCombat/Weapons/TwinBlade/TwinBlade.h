// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwinBlade.generated.h"

/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ATwinBlade : public ACharacterWeapon
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void OnPrimaryAttack() override;
	
	
};
