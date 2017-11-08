// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"
#include "TimerManager.h"
#include "Engine/Engine.h" // For debug delete later.
#include "Components/BoxComponent.h"
#include <string>


void ATwinBlade::BeginPlay(){
	Super::BeginPlay();
	BoxComponent = FindComponentByClass<UBoxComponent>();
	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATwinBlade::OnSwordHit);
	
}


void ATwinBlade::OnPrimaryAttack(){
	Super::OnPrimaryAttack();
	UE_LOG(LogTemp, Warning, TEXT("ATwinBlade >> OnPrimaryAttack"));
	
	/*Save combo*/
	if (bSaveCombo){	SaveCombo();	}

	if (CombatCharacter->IsReadyToAttack()){	PrimaryAttack();	}

}

void ATwinBlade::EnableWeaponCollider(){
	if (BoxComponent == nullptr) { return; }
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
}

void ATwinBlade::DisableWeaponCollider(){
	if (BoxComponent == nullptr) { return; }
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

