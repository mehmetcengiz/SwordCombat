// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
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


};
