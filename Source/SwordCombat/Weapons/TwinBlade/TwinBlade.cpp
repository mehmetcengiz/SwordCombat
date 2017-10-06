// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"
#include "ConstructorHelpers.h"

void UTwinBlade::OnPrimaryAttack() {
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwinBlade > OnPrimaryAttack called."))
}

void UTwinBlade::BeginPlay(){
	Super::BeginPlay();
}
