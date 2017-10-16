// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractState.h"
#include "SwordCombatCharacter.h"
#include "Engine/Engine.h"

void UInteractState::OnRightButtonPressed() {
	Super::OnRightButtonPressed();
	auto Character = static_cast<ASwordCombatCharacter*>(GetOwner());
	Character->SwitchCharacterState(ECharacterState::COMBAT);
}

void UInteractState::BeginPlay(){
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 555.f, FColor::Green, GetOwner()->GetName());
	auto Character = static_cast<ASwordCombatCharacter*>(GetOwner());
	Character->SetAnimationInstanceToDefault();
	Character->PutSwordBackToSheath();
}


