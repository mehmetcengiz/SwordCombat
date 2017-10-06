// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"

void UTwinBlade::OnPrimaryAttack() {
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwinBlade > OnPrimaryAttack called."))
}

void UTwinBlade::OnComponentCreated(){
	Super::OnComponentCreated();
	UE_LOG(LogTemp, Warning, TEXT("Twinblade >> OnComponent Created"));
}

void UTwinBlade::BeginPlay(){
	Super::BeginPlay();
}
