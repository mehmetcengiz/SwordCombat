// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "SwordCombatCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "CharacterWeapon.generated.h"

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
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ASwordCombatCharacter* CombatCharacter = nullptr;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void EnableWeaponCollider();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DisableWeaponCollider();

};
