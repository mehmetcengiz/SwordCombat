// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoHandedWeapon.h"


void UTwoHandedWeapon::OnPrimaryAttack(){
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwoHandedWeapon > OnPrimaryAttack called."))
}
