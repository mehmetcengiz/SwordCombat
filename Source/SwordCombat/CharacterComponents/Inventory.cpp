// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "./Weapons/CharacterWeapon.h"
#include "Engine/Texture2D.h"


// Sets default values for this component's properties
UInventory::UInventory(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay(){
	Super::BeginPlay();

	UpdateInventory();

}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//for (FInventoryItem item : InventoryItems){
	//	UE_LOG(LogTemp, Warning, TEXT("I Have %s "), *item.Name);
	//}
}

void UInventory::SetPrimaryWeapon(ACharacterWeapon* WeaponToSet){
	PrimaryWeapon = WeaponToSet;
}

void UInventory::UpdateInventory(){
	OnUpdateInventory.Broadcast(InventoryItems);
}

void UInventory::AddItem(FInventoryItem Item){
	if (InventoryItems.Num() < InventorySize){
		InventoryItems.Add(Item);
	}
	UpdateInventory();
}

void UInventory::UseItem(FInventoryItem Item){

	switch (Item.ItemType){
	case EItemType::NONE:
		UE_LOG(LogTemp, Warning, TEXT("Item Type None"));
		break;
	case EItemType::WEAPON:
		UE_LOG(LogTemp, Warning, TEXT("Item Type WEAPON"));
		break;
	case EItemType::HELMET:
		UE_LOG(LogTemp, Warning, TEXT("Item Type HELMET"));
		break;
	case EItemType::POTION:
		UE_LOG(LogTemp, Warning, TEXT("Item Type POTION"));
		break;
	default: ;
	}

}

void UInventory::DeleteItem(int32 Slot){
	if (Slot < InventoryItems.Num()){
		InventoryItems.RemoveAt(Slot);
		UpdateInventory();
	}
}
