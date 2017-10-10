// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwinBlade.generated.h"


class UAnimMontage;
class ACharacter;
/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ATwinBlade : public ACharacterWeapon
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* Attack2;


	
	void BeginPlay() override;
	void OnPrimaryAttack() override;

	
};
