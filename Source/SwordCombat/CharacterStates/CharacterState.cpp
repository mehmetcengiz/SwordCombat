// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterState.h"
#include "./Weapons/CharacterWeapon.h"


// Sets default values for this component's properties
UCharacterState::UCharacterState(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterState::BeginPlay(){
	Super::BeginPlay();
	
	

}



// Called every frame
void UCharacterState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCharacterState::OnRightButtonPressed(){
	UE_LOG(LogTemp, Warning, TEXT("CharacterState.cpp > OnRightButtonPressed called."));

}

UAnimBlueprint* UCharacterState::GetAnimInstance(){
	return nullptr;
}


