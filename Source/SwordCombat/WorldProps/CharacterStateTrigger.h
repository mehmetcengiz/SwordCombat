// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterStateTrigger.generated.h"

UENUM()
enum class ECharacterState : uint8 {
	INTERACTSTATE	UMETA(DisplayName = "Interact State"),
	COMBATSTATE		UMETA(DisplayName = "Combat State")
};

UCLASS()
class SWORDCOMBAT_API ACharacterStateTrigger : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACharacterStateTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	TEnumAsByte<ECharacterState> CharacterState;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
