// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeaponActor.h"
#include "TwoHandedWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ATwoHandedWeaponActor : public ACharacterWeaponActor
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void OnPrimaryAttack() override;
	
	
};
