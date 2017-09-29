// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwoHandedWeapon.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWORDCOMBAT_API UTwoHandedWeapon : public UCharacterWeapon
{
	GENERATED_BODY()
protected:
	virtual void OnPrimaryAttack() override;	
};
