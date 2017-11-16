// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./WorldProps/CharacterStateTrigger.h"
#include "SwordCombatCharacter.generated.h"


class UCharacterState;
class ACharacterWeapon;
class UInventory;
class UAnimMontage;

UCLASS(config=Game)
class ASwordCombatCharacter : public ACharacter
{
	GENERATED_BODY()
	
	
	/*
	 *Components
	 */

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category= "Combat Component")
	UCharacterState* CharacterState = nullptr;


	/*Inventory*/
	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInventory* CharacterInventory = nullptr;



	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TSubclassOf<UAnimInstance> DefaultAnimation;
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ACharacterWeapon* GetPrimaryWeapon() const;
	/*
	 *End Components 
	 */
	
	/*Constructer,Beginplay,Tick*/
public:
	ASwordCombatCharacter();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
	/*Setup*/
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void SetDodgingMontages(UAnimMontage* Forward, UAnimMontage* Backward, UAnimMontage* Left, UAnimMontage* Right);
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SetAnimationInstance(UClass* AnimInstanceToSet);

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SetAnimationInstanceToDefault();
	void SetPlayerRotationToFocusedEnemy();

	/*End Setters*/

	/*Character Stats*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Stats")
	float MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, Category = "Character Stats")
	float CurrentHealth = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Stats")
	float Dex = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	float FocusedSpeed = 325;
	UPROPERTY(EditDefaultsOnly, Category = "Character")
	float DefaultSpeed = 400;

public:
	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SwitchCharacterState(ECharacterState CharacterStateEnum);
	float GetDex() const { return Dex; }

	/*Controls and Mechanics*/
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	/**Executes when PrimaryAttack pressed.*/
	void OnRightButtonPressed();

protected:
	/*Focusing control*/
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void AddActorToCloseAttackerList(AActor* ActorToFocus);
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void RemoveActorFromCloseAttackerList(AActor* ActorToRemove);
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	TArray<AActor*> GetCloseAttackerList() const{ return CloseAttackerList; }
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void ToggleFocusToCharacter();
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void FocusToNextEnemy();
	UFUNCTION(BlueprintCallable, Category = "Attacking")
	void FocusToPrevEnemy();

	bool bIsCharacterFocused = false; // TODO make private later.
	int32 FocusedCharacterIndex = 0; // TODO make private later.


	UPROPERTY()
	TArray<AActor*> CloseAttackerList;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	
private:
	UAnimMontage* DodgeForward = nullptr;
	UAnimMontage* DodgeBackward = nullptr;
	UAnimMontage* DodgeLeft = nullptr;
	UAnimMontage* DodgeRight = nullptr;

public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(UClass* WeaponClass);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetForwardValue() const { return MoveForwardValue; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRightValue() const { return MoveRightValue; }

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	bool GetIsFocusedToEnemy() const { return bIsCharacterFocused; }

	void DisableAttackingForCertainTime(float TimeToDisable);
	void DisableAttacking();
	void EnableAttacking();
	bool IsReadyToAttack() const{ return bIsReadyToAttack; }
	void TakeHit(float Damage, float DamageLocation);
	void PutSwordBackToSheath();
	void ResetCharacter();
	void Dodge();

	UPROPERTY(BlueprintReadWrite,Category="Animations")
	bool bGotHit = false;
	UPROPERTY(BlueprintReadWrite,Category="Animations")
	bool bIsDeath = false;
	UPROPERTY(BlueprintReadWrite,Category="Animations")
	float LastDamageLocation = 0;

	float DisableAttackingOnHitTime = 0.2f;

	
private:
	ECharacterState CurrentCharacterState = ECharacterState::INTERACT;
	bool bIsReadyToAttack = true;
	
	void PlayDeath();
	void DisableFromWorld();

protected:
	float MoveForwardValue = 0;
	float MoveRightValue = 0;


};

