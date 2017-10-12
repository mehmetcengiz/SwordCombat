// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWeapon.h"


void ACharacterWeapon::BeginPlay(){
	Super::BeginPlay();
}

void ACharacterWeapon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACharacterWeapon::OnPrimaryAttack(){
	UE_LOG(LogTemp, Warning, TEXT("CharacterWeapon >> "));
	//TODO I left here. Create 2 weapon actors by using this class as base class.
}

void ACharacterWeapon::InitializeCharacterWeapon(ASwordCombatCharacter* CharacterToSet){
	UE_LOG(LogTemp, Warning, TEXT("CharacterWeapon >> Init"));
	CombatCharacter = CharacterToSet;
	
}

void ACharacterWeapon::EnableWeaponCollider(){
	
}

void ACharacterWeapon::DisableWeaponCollider(){
	
}

