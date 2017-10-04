// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinBlade.h"

void UTwinBlade::OnPrimaryAttack() {
	Super::OnPrimaryAttack();

	UE_LOG(LogTemp, Warning, TEXT("TwinBlade > OnPrimaryAttack called."))
}

void UTwinBlade::BeginPlay(){
	Super::BeginPlay();

}

void UTwinBlade::SetWeaponStaticMesh(UStaticMeshComponent* WeaponMesh_RToSet, UStaticMeshComponent* WeaponMesh_LToSet){
	WeaponMesh_L = WeaponMesh_LToSet;
	WeaponMesh_R = WeaponMesh_RToSet;
}