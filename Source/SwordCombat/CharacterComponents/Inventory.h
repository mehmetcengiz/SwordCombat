// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class ACharacterWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class SWORDCOMBAT_API UInventory : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACharacterWeaponActor* PrimaryWeapon = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void SetPrimaryWeapon(ACharacterWeaponActor* WeaponToSet);

	ACharacterWeaponActor* GetPrimaryWeapon() const { return PrimaryWeapon; };

	
};
