// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatState.h"
#include "SwordCombatCharacter.h"
#include "./Weapons/CharacterWeapon.h"
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
	//Get primary weapon.
	auto Character = static_cast<ASwordCombatCharacter*>(GetOwner());
	CharacterWeapon = Character->GetPrimaryWeapon();

	//Set to a hand socket.
	if (CharacterWeapon == NULL) { return; }
	auto CharacterMesh = Character->GetMesh();
	FName fnWeaponSocket = TEXT("ik_hand_gun");
	CharacterWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, fnWeaponSocket);

	//TODO Set weapon animation to character.
	Character->SetAnimationInstance(CharacterWeapon->GetWeaponAnimInstance());

}