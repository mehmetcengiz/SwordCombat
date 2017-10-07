// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBladeActor.h"


void ATwinBladeActor::BeginPlay(){
	Super::BeginPlay();
}

void ATwinBladeActor::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBladeActor >> OnPrimaryAttack"));
}
