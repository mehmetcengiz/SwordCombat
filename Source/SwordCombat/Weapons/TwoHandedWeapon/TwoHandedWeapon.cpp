// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoHandedWeapon.h"


void UTwoHandedWeapon::OnPrimaryAttack(){
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwoHandedWeapon > OnPrimaryAttack called."))
}

void UTwoHandedWeapon::OnComponentCreated(){
	Super::OnComponentCreated();
	UE_LOG(LogTemp, Warning, TEXT("Twinblade >> OnComponent Created"));
}
