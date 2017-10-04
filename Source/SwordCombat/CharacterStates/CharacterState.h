// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterState.generated.h"

class UCharacterWeapon;
class UAnimBlueprint;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDCOMBAT_API UCharacterState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRightButtonPressed();
	
	virtual UAnimBlueprint* GetAnimInstance();
};
