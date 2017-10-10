// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"

void ATwinBlade::BeginPlay(){
	Super::BeginPlay();
}

void ATwinBlade::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBlade >> OnPrimaryAttack"));

	float MontageTime = CombatCharacter->GetMesh()->GetAnimInstance()->Montage_Play(Attack2, 1.0f, EMontagePlayReturnType::MontageLength, 0);
	static_cast<ASwordCombatCharacter*>(CombatCharacter)->DisableInputForCertainTime(MontageTime / 2);

}
