// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


class ACharacterWeapon;
class UTexture2D;

UENUM(BlueprintType)
enum class EItemType : uint8{
	NONE	UMETA(DisplayName = "None"),
	WEAPON	UMETA(DisplayName = "Weapon"),
	HELMET	UMETA(DisplayName = "Helmet"),
	POTION	UMETA(DisplayName = "Potion"),
};

USTRUCT(BlueprintType)
struct FInventoryItem{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Item")
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 Slot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* Image;


	FString GetName() const{ return Name; }
	UTexture2D* GetTexture2D() const{ return Image; }
	void SetName(FString NameToSet) { Name = NameToSet; }
	void SetImage(UTexture2D* ImageToSet) { Image = ImageToSet; }


	FInventoryItem(){
		
	}	

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<FInventoryItem>&, InventoryItems);

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
	
	UFUNCTION(BlueprintCallable,Category="Inventory")
	int32 GetInventorySize() const{ return InventorySize; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetInventoryItems() const { return InventoryItems; }

	UFUNCTION(BlueprintCallable,Category="Inventory")
	void UpdateInventory();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FUpdateInventoryDelegate OnUpdateInventory;	

	UFUNCTION(BlueprintCallable, Category = "Inventory Management")
	void AddItem(FInventoryItem Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory Management")
	void UseItem(FInventoryItem Item);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory Management")
	void DeleteItem(int32 Slot);

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 InventorySize = 20;

	void UseWeapon(FInventoryItem Item);

	
};
