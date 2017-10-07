// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CharacterWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class SWORDCOMBAT_API ACharacterWeaponActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnPrimaryAttack();


};
