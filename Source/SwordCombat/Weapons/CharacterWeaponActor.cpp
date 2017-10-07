// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWeaponActor.h"


void ACharacterWeaponActor::BeginPlay(){
	Super::BeginPlay();
}

void ACharacterWeaponActor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACharacterWeaponActor::OnPrimaryAttack(){
	UE_LOG(LogTemp, Warning, TEXT("CharacterWeaponActor >> "));
	//TODO I left here. Create 2 weapon actors by using this class as base class.
}
