// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"
#include "TimerManager.h"
#include "Engine/Engine.h" // For debug delete later.


void ATwinBlade::BeginPlay(){
	Super::BeginPlay();
}

void ATwinBlade::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBlade >> OnPrimaryAttack"));
	
	if(bSaveCombo){
		SaveCombo();
		bSaveCombo = false;
	}

	if (CombatCharacter->IsReadyToAttack()){
		
		//Play montage and set character is ready to attacking to false. 
		float MontageTime = CombatCharacter->GetMesh()->GetAnimInstance()->Montage_Play(PrimaryAttackCombos[PrimaryAttackIndex], 1.0f, EMontagePlayReturnType::MontageLength, 0);
		CombatCharacter->DisableAttackingForCertainTime(MontageTime / 3);

		//Set min max times for combo trigger. 
		NextComboMinTime = MontageTime / 3;
		NextComboMaxTime = MontageTime;

		//Execute saving combo trigger and reseting combo by times.
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ATwinBlade::EnableSaveCombo, NextComboMinTime, false);
		FTimerHandle Handle2;
		GetWorld()->GetTimerManager().SetTimer(OUT Handle2, this, &ATwinBlade::ResetCombo, NextComboMaxTime, false);
	
	}
}

void ATwinBlade::SaveCombo(){
	//TODO save combo;
	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, "Next Combo Triggered.");
	PrimaryAttackIndex++;
	if(PrimaryAttackIndex>=PrimaryAttackCombos.Num()){
		ResetCombo();
	}
}

void ATwinBlade::ResetCombo() {
	if(bSaveCombo){
		GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Red, "Combo Reseted");
		bSaveCombo = false;
		PrimaryAttackIndex = 0;
		//Reset combo.
	}
}
