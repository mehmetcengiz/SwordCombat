// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStates/CharacterState.h"
#include "CombatState.generated.h"


class UCharacterWeapon;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWORDCOMBAT_API UCombatState : public UCharacterState
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UCharacterWeapon* CharacterWeapon = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Equip Weapon")
	void EquipWeapon(UCharacterWeapon* EquippedWeapon);
	
public:
	void OnRightButtonPressed() override;
	
	
	
};