// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWeapon.h"


void ACharacterWeapon::BeginPlay(){
	Super::BeginPlay();
}

void ACharacterWeapon::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACharacterWeapon::OnPrimaryAttack(){
	UE_LOG(LogTemp, Warning, TEXT("CharacterWeapon >> "));
	//TODO I left here. Create 2 weapon actors by using this class as base class.
}

void ACharacterWeapon::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {

	//If actor has tag and actor has not hited before and actor not hited himself.
	if (OtherActor->ActorHasTag(FName("Enemy")) && !HitActors.Contains(OtherActor->GetOwner()) && OtherActor->GetOwner() != CombatCharacter) {
		HitActors.Add(OtherActor->GetOwner());
		//TODO hit to actor.
		//TODO Get hit location.

		float Angle = GetHitAngle(OtherActor);

		static_cast<ASwordCombatCharacter*>(OtherActor)->TakeHit(30, Angle);//TODO implement damage later.
	}
}

void ACharacterWeapon::InitializeCharacterWeapon(ASwordCombatCharacter* CharacterToSet){
	UE_LOG(LogTemp, Warning, TEXT("CharacterWeapon >> Init"));
	CombatCharacter = CharacterToSet;
	
}

void ACharacterWeapon::SaveCombo() {
	//TODO save combo;
	PrimaryAttackIndex++;
	if (PrimaryAttackIndex >= PrimaryAttackCombos.Num()) {
		ResetCombo();
	}
	bSaveCombo = false;
}

void ACharacterWeapon::ResetCombo() {
	if (bSaveCombo) {
		bSaveCombo = false;
		PrimaryAttackIndex = 0;
		//Reset combo.
	}
}

void ACharacterWeapon::EnableWeaponCollider(){
	
}

void ACharacterWeapon::DisableWeaponCollider(){
	
}

float ACharacterWeapon::GetHitAngle(AActor* OtherActor) const{

	auto OtherActForwardVector = OtherActor->GetActorForwardVector();
	auto CombatActForward = CombatCharacter->GetActorForwardVector();

	auto OtherActRotator = FRotationMatrix::MakeFromX(OtherActForwardVector).Rotator();
	auto CombatActRotator = FRotationMatrix::MakeFromX(CombatActForward).Rotator();

	auto DeltaRotator = OtherActRotator - CombatActRotator;
	DeltaRotator.Normalize();

	return DeltaRotator.Yaw;
}
