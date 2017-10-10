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

private:
	/**Min time for player to press attack again to execute next combo.*/
	UPROPERTY()
	float NextComboMinTime = 0.5f;
	/**Max time for player to press attack again to execute next combo.*/
	UPROPERTY()
	float NextComboMaxTime = 1.0f;

	bool bSaveCombo = false;

	void EnableSaveCombo()	{ bSaveCombo = true;	}
	void SaveCombo();
	void ResetCombo();
	


protected:	
	void BeginPlay() override;
	void OnPrimaryAttack() override;

	
};
