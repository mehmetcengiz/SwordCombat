// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwinBlade.generated.h"


class UAnimMontage;
class ACharacter;
class UBoxComponent;
/**
 * 
 */
UCLASS()

class SWORDCOMBAT_API ATwinBlade : public ACharacterWeapon {
	GENERATED_BODY()
protected:

	void BeginPlay() override;

	UBoxComponent* BoxComponent = nullptr;
	
protected:
	void OnPrimaryAttack() override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EnableWeaponCollider() override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DisableWeaponCollider() override;

};
