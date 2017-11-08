// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwoHandedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ATwoHandedWeapon : public ACharacterWeapon
{
	GENERATED_BODY()

private:

	void PrimaryAttack();



protected:
	void BeginPlay() override;
	void OnPrimaryAttack() override;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EnableWeaponCollider() override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DisableWeaponCollider() override;
};
