// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatState.h"
#include "SwordCombatCharacter.h"
#include "./Weapons/CharacterWeaponActor.h"
#include "./Components/SkeletalMeshComponent.h"

void UCombatState::OnRightButtonPressed(){
	Super::OnRightButtonPressed();

	UE_LOG(LogTemp, Warning, TEXT("Combat State> OnRightButtonPressed."));

	if (CharacterWeapon == NULL){
		UE_LOG(LogTemp, Error, TEXT("Combat State> Character Weapon is null."));
		DrawPrimaryWeapon();
		return;
	}

	CharacterWeapon->OnPrimaryAttack();
}

void UCombatState::DrawPrimaryWeapon() {
	
	auto Character = static_cast<ASwordCombatCharacter*>(GetOwner());
	CharacterWeapon = Character->GetPrimaryWeapon();
	if (CharacterWeapon == NULL) { return; }
	auto CharacterMesh = Character->GetMesh();

	FName fnWeaponSocket = TEXT("ik_hand_gun");
	CharacterWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, fnWeaponSocket);
}