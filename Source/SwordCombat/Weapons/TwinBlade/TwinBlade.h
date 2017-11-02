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
	void GetCharacterHitAngleByCombatCharacter(AActor* OtherActor, float& Angle);

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* Attack2;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> PrimaryAttackCombos;

	UBoxComponent* BoxComponent = nullptr;
	TArray<AActor*> HitActors;

private:
	/**Min time for player to press attack again to execute next combo.*/
	UPROPERTY()
	float NextComboMinTime = 0.5f;
	/**Max time for player to press attack again to execute next combo.*/
	UPROPERTY()
	float NextComboMaxTime = 1.0f;

	bool bSaveCombo = false;

	void EnableSaveCombo(){ bSaveCombo = true; }
	void SaveCombo();
	void ResetCombo();
	void PrimaryAttack();

	int32 PrimaryAttackIndex = 0;

	UFUNCTION(BlueprintCallable,Category= "SwordHit")
	void OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float GetHitAngle(AActor* OtherActor);


protected:
	void OnPrimaryAttack() override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EnableWeaponCollider() override;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DisableWeaponCollider() override;

};
