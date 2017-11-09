// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./WorldProps/CharacterStateTrigger.h"
#include "SwordCombatCharacter.generated.h"


class UCharacterState;
class ACharacterWeapon;
class UInventory;

UCLASS(config=Game)
class ASwordCombatCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ASwordCombatCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category= "Combat Component")
	UCharacterState* CharacterState = nullptr;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "Character State")
	void SwitchCharacterState(ECharacterState CharacterStateEnum);

protected:


	// Called when the game starts
	virtual void BeginPlay() override;
	void SetPlayerRotationToFocusedEnemy();
	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION(BlueprintCallable, Category = "Attacking")
	bool GetIsFocusedToEnemy() const { return bIsCharacterFocused; }

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

	/**Executes when PrimaryAttack pressed.*/
	void OnRightButtonPressed();
	
	/*Inventory*/
	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInventory* CharacterInventory = nullptr;
	
	UPROPERTY(EditDefaultsOnly,Category = "Character")
	float FocusedSpeed = 325;
	UPROPERTY(EditDefaultsOnly,Category = "Character")
	float DefaultSpeed = 400;

public:
	UFUNCTION(BlueprintCallable,Category="Animations")
	void SetAnimationInstance(UClass* AnimInstanceToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SetAnimationInstanceToDefault();

	UFUNCTION(BlueprintCallable,Category="Weapon")
	ACharacterWeapon* GetPrimaryWeapon() const;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(UClass* WeaponClass);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetForwardValue() const { return MoveForwardValue; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRightValue() const { return MoveRightValue; }

	void DisableAttackingForCertainTime(float TimeToDisable);
	void DisableAttacking();
	void EnableAttacking();
	bool IsReadyToAttack() const{ return bIsReadyToAttack; }
	void TakeHit(float Damage, float DamageLocation);
	void PutSwordBackToSheath();
	void ResetCharacter();

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
	
private:
	void PlayDeath();
	void DisableFromWorld();


protected:
	UPROPERTY(EditDefaultsOnly,Category="Character Stats")
	float MaxHealth = 100;

	UPROPERTY(BlueprintReadWrite,Category="Character Stats")
	float CurrentHealth = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TSubclassOf<UAnimInstance> DefaultAnimation;

	float MoveForwardValue = 0;
	float MoveRightValue = 0;


};

