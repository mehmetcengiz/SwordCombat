// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CharacterWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class SWORDCOMBAT_API UCharacterWeapon : public USceneComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PrimaryAttack();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
