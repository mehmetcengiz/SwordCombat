// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "SwordCombatCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "CharacterWeapon.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ACharacterWeapon : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnPrimaryAttack();

	void InitializeCharacterWeapon(ASwordCombatCharacter* CharacterToSet);
	UClass* GetWeaponAnimInstance() const{return WeaponAnimInstance;}
	

	FName GetWeaponSocketName() const { return WeaponSocketName; }
		
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<UAnimMontage*> PrimaryAttackCombos;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DodgeForward;//TODO do private later.

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DodgeBackward;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DodgeLeft;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DodgeRight;
protected:

	UBoxComponent* BoxComponent = nullptr;

	TArray<AActor*> HitActors;	


	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ASwordCombatCharacter* CombatCharacter = nullptr;
	
	UFUNCTION(BlueprintCallable, Category = "SwordHit")
		void OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PrimaryAttack();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void EnableWeaponCollider();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DisableWeaponCollider();

	UPROPERTY(EditDefaultsOnly,Category="Animations")
	TSubclassOf<UAnimInstance> WeaponAnimInstance;


	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName = "TwoHandedSwordSheath";


	/**Min time for player to press attack again to execute next combo.*/
	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	float NextComboMinTime = 0.5f;
	/**Max time for player to press attack again to execute next combo.*/
	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	float NextComboMaxTime = 1.0f;

	bool bSaveCombo = false;

	void EnableSaveCombo() { bSaveCombo = true; }
	void SaveCombo();
	void ResetCombo();


	int32 PrimaryAttackIndex = 0;

	float GetHitAngle(AActor* OtherActor) const;

};
