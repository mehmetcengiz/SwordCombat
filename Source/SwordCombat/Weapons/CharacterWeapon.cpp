// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWeapon.h"


// Sets default values for this component's properties
UCharacterWeapon::UCharacterWeapon(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UCharacterWeapon::BeginPlay(){
	Super::BeginPlay();

}

void UCharacterWeapon::OnPrimaryAttack(){
	UE_LOG(LogTemp,Warning,TEXT("CharacterWeapon > OnPrimaryAttack called."))
}

// Called every frame
void UCharacterWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UAnimBlueprint* UCharacterWeapon::GetAnimInstance() const{
	return CharacterAnimationInstance;
}