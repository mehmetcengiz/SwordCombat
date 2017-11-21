// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordCombatAIController.h"
#include "SwordCombatCharacter.h"


void ASwordCombatAIController::PrimaryAttack(){
	UE_LOG(LogTemp, Warning, TEXT("SWORD AI Attackin !!!!"));

	auto Character = Cast<ASwordCombatCharacter>(GetControlledPawn());
	if (!ensure(Character)) { return; }
	Character->OnRightButtonPressed();

}

void ASwordCombatAIController::FaceToEnemy(AActor * EnemyToFace){
	auto Character = Cast<ASwordCombatCharacter>(GetControlledPawn());
	if (!ensure(Character)) { return; }
	Character->FaceToEnemy(EnemyToFace);
}
