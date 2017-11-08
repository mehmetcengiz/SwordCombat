// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"
#include "TimerManager.h"
#include "Engine/Engine.h" // For debug delete later.
#include <string>


void ATwinBlade::BeginPlay(){
	Super::BeginPlay();
	
}


void ATwinBlade::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBlade >> OnPrimaryAttack"));
	
	/*Save combo*/
	if (bSaveCombo){	SaveCombo();	}

	if (CombatCharacter->IsReadyToAttack()){	PrimaryAttack();	}

}
