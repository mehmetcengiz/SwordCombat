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

void ATwinBlade::OnSwordHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult){

	//If actor has tag and actor has not hited before and actor not hited himself.
	if(OtherActor->ActorHasTag(FName("Enemy")) && !HitActors.Contains(OtherActor->GetOwner()) && OtherActor->GetOwner() != CombatCharacter){
		HitActors.Add(OtherActor->GetOwner());
		//TODO hit to actor.
		//TODO Get hit location.
		
		float Angle = GetHitAngle(OtherActor);
	
		static_cast<ASwordCombatCharacter*>(OtherActor)->TakeHit(30, Angle);//TODO implement damage later.
	}
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

void ATwinBlade::SaveCombo(){
	//TODO save combo;
	PrimaryAttackIndex++;
	if (PrimaryAttackIndex >= PrimaryAttackCombos.Num()){
		ResetCombo();
	}
	bSaveCombo = false;
}

void ATwinBlade::ResetCombo(){
	if (bSaveCombo){
		bSaveCombo = false;
		PrimaryAttackIndex = 0;
		//Reset combo.
	}
}

float ATwinBlade::GetHitAngle(AActor* OtherActor){

	auto OtherActForwardVector = OtherActor->GetActorForwardVector();
	auto CombatActForward = CombatCharacter->GetActorForwardVector();

	auto OtherActRotator = FRotationMatrix::MakeFromX(OtherActForwardVector).Rotator();
	auto CombatActRotator = FRotationMatrix::MakeFromX(CombatActForward).Rotator();

	auto DeltaRotator = OtherActRotator - CombatActRotator;
	DeltaRotator.Normalize();

	return DeltaRotator.Yaw;
}

void ATwinBlade::PrimaryAttack() {
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

	//Clear the hit actor array.
	HitActors.Empty();
}