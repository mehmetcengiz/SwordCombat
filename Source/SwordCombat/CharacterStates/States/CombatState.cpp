// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatState.h"
#include "SwordCombatCharacter.h"
#include "./Weapons/CharacterWeapon.h"

void UCombatState::EquipWeapon() {
	CharacterWeapon = static_cast<ASwordCombatCharacter*>(GetOwner())->GetPrimaryWeapon();
}

void UCombatState::OnRightButtonPressed(){
	Super::OnRightButtonPressed();

	UE_LOG(LogTemp, Warning, TEXT("Combat State> OnRightButtonPressed."));

	if (CharacterWeapon == NULL){
		EquipWeapon();
		UE_LOG(LogTemp, Error, TEXT("Combat State> Character Weapon is null."));
		return;
	}

	CharacterWeapon->OnPrimaryAttack();

}
