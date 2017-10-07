// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoHandedWeaponActor.h"

void ATwoHandedWeaponActor::BeginPlay(){
	Super::BeginPlay();
}

void ATwoHandedWeaponActor::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwoHandedWeaponActor >> OnPrimaryAttack"));
}


