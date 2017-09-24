// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterCombat.generated.h"

class UCharacterWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDCOMBAT_API UCharacterCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCombat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category= "Weapon")
	UCharacterWeapon* CharacterWeapon = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Equip Weapon")
	void EquipWeapon(UCharacterWeapon* EquippedWeapon);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PrimaryAttack();
};
