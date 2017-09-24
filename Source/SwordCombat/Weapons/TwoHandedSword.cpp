// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoHandedSword.h"


void UTwoHandedSword::OnPrimaryAttack(){
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwoHandedSword > OnPrimaryAttack called."))
}
