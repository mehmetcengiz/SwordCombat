// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoHandedWeapon.h"

void ATwoHandedWeapon::BeginPlay(){
	Super::BeginPlay();
}

void ATwoHandedWeapon::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwoHandedWeapon >> OnPrimaryAttack"));
}


