// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConstructorHelpers.h"
#include "CharacterWeapon.generated.h"

class UAnimBlueprint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class SWORDCOMBAT_API UCharacterWeapon : public UStaticMeshComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/**Damage*/
	UPROPERTY(EditDefaultsOnly,Category="Weapon Stats")
	float Damage = 10;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnComponentCreated();
	virtual void OnPrimaryAttack();
};
