// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/CharacterWeapon.h"
#include "TwinBlade.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWORDCOMBAT_API UTwinBlade : public UCharacterWeapon
{
	GENERATED_BODY()
protected:
	virtual void OnPrimaryAttack() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	/**Weapon mesh. */
	UPROPERTY()
	UStaticMeshComponent* WeaponMesh_R = nullptr;
	/**Weapon mesh. */
	UPROPERTY()
	UStaticMeshComponent* WeaponMesh_L = nullptr;

	/*Setting weapon static mesh*/
	UFUNCTION(BlueprintCallable, Category = "Weapons Mesh")
	void SetWeaponStaticMesh(UStaticMeshComponent* WeaponMesh_RToSet, UStaticMeshComponent* WeaponMesh_LToSet);
	
};
