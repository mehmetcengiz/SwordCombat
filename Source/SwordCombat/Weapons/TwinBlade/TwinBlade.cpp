// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"


void ATwinBlade::BeginPlay(){
	Super::BeginPlay();
}

void ATwinBlade::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBlade >> OnPrimaryAttack"));
}
