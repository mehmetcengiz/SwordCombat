// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class ACharacterWeapon;
class UTexture2D;


USTRUCT(BlueprintType)
struct FInventoryItem{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 Quantity;	
	
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 ItemSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UTexture2D* Image;


	FString GetName() const{ return Name; }
	UTexture2D* GetTexture2D() const{ return Image; }
	void SetName(FString NameToSet) { Name = NameToSet; }
	void SetImage(UTexture2D* ImageToSet) { Image = ImageToSet; }


	FInventoryItem(){
		
	}	

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class SWORDCOMBAT_API UInventory : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	ACharacterWeapon* PrimaryWeapon = nullptr;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void SetPrimaryWeapon(ACharacterWeapon* WeaponToSet);

	ACharacterWeapon* GetPrimaryWeapon() const { return PrimaryWeapon; }

	UPROPERTY(EditAnywhere,Category="Inventory")
	TArray<FInventoryItem> InventoryItems;
	
	TArray<FInventoryItem> GetInventoryItems() const { return InventoryItems; }
};
