// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SwordCombatCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "./SwordCombat/CharacterStates/CharacterState.h"
#include "./CharacterStates/States/CombatState.h"
#include "./CharacterStates/States/InteractState.h"
#include "./CharacterComponents/Inventory.h"
#include "./Weapons/CharacterWeapon.h"
#include "./Components/SkeletalMeshComponent.h"
#include "TimerManager.h"

//////////////////////////////////////////////////////////////////////////
// ASwordCombatCharacter

ASwordCombatCharacter::ASwordCombatCharacter(){

	//Tick enabled
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	CharacterInventory = CreateDefaultSubobject<UInventory>(TEXT("Character Inventory"));

}

//////////////////////////////////////////////////////////////////////////
// Input

void ASwordCombatCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("FocusToEnemy", IE_Pressed, this, &ASwordCombatCharacter::ToggleFocusToCharacter);
	/*PlayerInputComponent->BindAction("FocusNextTarget", IE_Pressed, this, &ASwordCombatCharacter::FocusToNextEnemy);
	PlayerInputComponent->BindAction("FocusPrevTarget", IE_Pressed, this, &ASwordCombatCharacter::FocusToPrevEnemy);*/

	PlayerInputComponent->BindAxis("MoveForward", this, &ASwordCombatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwordCombatCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASwordCombatCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASwordCombatCharacter::LookUpAtRate);


	//Combat attack.
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASwordCombatCharacter::OnRightButtonPressed);
}

void ASwordCombatCharacter::BeginPlay(){
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Game has started."));

	/*Create default chracter state*/
	SwitchCharacterState(ECharacterState::COMBAT);

	//TODO Later set animation instance depends on weapon for every enemy. 
	if (this->ActorHasTag(FName("Player"))){
		SetAnimationInstanceToDefault();
	}

	CurrentHealth = MaxHealth;

}

void ASwordCombatCharacter::SetPlayerRotationToFocusedEnemy(){
	UE_LOG(LogTemp, Warning, TEXT("Player is focusing !!!!!!!!!!!!"));
	if (!(CloseAttackerList.Num() > FocusedCharacterIndex)){ return; }
	FVector Direction = CloseAttackerList[FocusedCharacterIndex]->GetActorLocation() - GetActorLocation();
	FRotator DesiredActorRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(DesiredActorRotation);
}

void ASwordCombatCharacter::Tick(float DeltaTime){


	if (bIsCharacterFocused){
		if (CloseAttackerList.Num() <= 0){ ToggleFocusToCharacter(); }
		SetPlayerRotationToFocusedEnemy();
	}


}

void ASwordCombatCharacter::AddActorToCloseAttackerList(AActor* ActorToFocus){
	if (!ActorToFocus->ActorHasTag(FName("Enemy"))){ return; }
	CloseAttackerList.Add(ActorToFocus);

}

void ASwordCombatCharacter::RemoveActorFromCloseAttackerList(AActor* ActorToRemove){
	if (!ActorToRemove->ActorHasTag(FName("Enemy"))){ return; }
	CloseAttackerList.Remove(ActorToRemove);
}

void ASwordCombatCharacter::ToggleFocusToCharacter(){
	if (bIsCharacterFocused){
		bIsCharacterFocused = false;
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
		CameraBoom->bUsePawnControlRotation = true;
	}
	else if (!bIsCharacterFocused){
		bIsCharacterFocused = true;
		GetCharacterMovement()->MaxWalkSpeed = FocusedSpeed;
		CameraBoom->bUsePawnControlRotation = false;
	}

}

void ASwordCombatCharacter::FocusToNextEnemy(){
	FocusedCharacterIndex++;
	FocusedCharacterIndex = FocusedCharacterIndex % CloseAttackerList.Num();
}

void ASwordCombatCharacter::FocusToPrevEnemy(){
	if (FocusedCharacterIndex <= 0) {
		FocusedCharacterIndex = CloseAttackerList.Num();
	}
	FocusedCharacterIndex--;

}


void ASwordCombatCharacter::OnRightButtonPressed(){
	if (CharacterState == NULL){
		UE_LOG(LogTemp, Error, TEXT("CharacterState is null!!"));
		return;
	}
	CharacterState->OnRightButtonPressed();
}

void ASwordCombatCharacter::SwitchCharacterState(ECharacterState CharacterStateEnum){

	if (CharacterStateEnum == ECharacterState::COMBAT && CurrentCharacterState != ECharacterState::COMBAT){
		UE_LOG(LogTemp, Warning, TEXT("Character state switched to Combat state"));
		CurrentCharacterState = ECharacterState::COMBAT;
		if (CharacterState)
			CharacterState->DestroyComponent(false);
		CharacterState = ConstructObject<UCombatState>(UCombatState::StaticClass(), this, TEXT("Combat State"));
		CharacterState->RegisterComponent();
		CharacterState->OnComponentCreated();

	}
	else if (CharacterStateEnum == ECharacterState::INTERACT && CurrentCharacterState != ECharacterState::INTERACT){
		UE_LOG(LogTemp, Warning, TEXT("Character state switched to Interact state"));
		CurrentCharacterState = ECharacterState::INTERACT;
		if (CharacterState)
			CharacterState->DestroyComponent(false);
		CharacterState = ConstructObject<UInteractState>(UInteractState::StaticClass(), this, TEXT("Interact State"));
		CharacterState->RegisterComponent();
		CharacterState->OnComponentCreated();
	}

}

void ASwordCombatCharacter::TurnAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());


}

void ASwordCombatCharacter::LookUpAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void ASwordCombatCharacter::MoveForward(float Value){
	MoveForwardValue = Value;
	if ((Controller != NULL) && (Value != 0.0f)){
		FVector Direction;
		// find out which way is forward
		
		FRotator Rotation;
		if (!bIsCharacterFocused){
			Rotation = Controller->GetControlRotation();
		}
		else{
			Rotation = GetActorRotation();
		}
		
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);

	}
}

void ASwordCombatCharacter::MoveRight(float Value){
	MoveRightValue = Value;
	if ((Controller != NULL) && (Value != 0.0f)){
		// find out which way is right
		
		FRotator Rotation;
		if (!bIsCharacterFocused){
			Rotation = Controller->GetControlRotation();
		}
		else{
			Rotation = GetActorRotation();
		}

		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction		

		AddMovementInput(Direction, Value);

	}
}

void ASwordCombatCharacter::SetAnimationInstance(UClass* AnimInstanceToSet){
	if (CharacterState == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Character State is NULL"));
		return;
	}
	//TODO switch animation depends on weapon animation or interactstate animations etc.

	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(AnimInstanceToSet);
}

void ASwordCombatCharacter::SetAnimationInstanceToDefault(){
	if (CharacterState == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Character State is NULL"));
		return;
	}
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(DefaultAnimation);
}

ACharacterWeapon* ASwordCombatCharacter::GetPrimaryWeapon() const{
	return CharacterInventory->GetPrimaryWeapon();
}

void ASwordCombatCharacter::EquipWeapon(UClass* WeaponClass){

	auto Weapon = GetWorld()->SpawnActor<ACharacterWeapon>(WeaponClass);
	FName fnWeaponSocket = Weapon->GetWeaponSocketName();

	const FVector spawnLocation = GetMesh()->GetSocketLocation(fnWeaponSocket);
	const FRotator spawnRotation = GetMesh()->GetSocketRotation(fnWeaponSocket);

	Weapon->SetActorRotation(spawnRotation);
	Weapon->SetActorLocation(spawnLocation);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, fnWeaponSocket);
	Weapon->InitializeCharacterWeapon(this);


	if (CharacterInventory){
		CharacterInventory->SetPrimaryWeapon(Weapon);
	}
}

void ASwordCombatCharacter::DisableAttackingForCertainTime(float TimeToDisable){
	bIsReadyToAttack = false;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ASwordCombatCharacter::EnableAttacking, TimeToDisable, false);
}

void ASwordCombatCharacter::DisableAttacking(){
	bIsReadyToAttack = false;
}

void ASwordCombatCharacter::EnableAttacking(){
	bIsReadyToAttack = true;
}

void ASwordCombatCharacter::PutSwordBackToSheath(){
	FName fnWeaponSocket = TEXT("TwinBladeSheath");

	if (CharacterInventory != NULL){
		CharacterInventory->GetPrimaryWeapon()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, fnWeaponSocket);
	}
}

void ASwordCombatCharacter::TakeHit(float Damage, float DamageLocation){
	UE_LOG(LogTemp, Warning, TEXT("I tooked hit !!!"));
	//TODO Play Animation. 
	bGotHit = true;
	bIsReadyToAttack = false;
	FTimerHandle Handle;
	LastDamageLocation = DamageLocation;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ASwordCombatCharacter::ResetCharacter, DisableAttackingOnHitTime, false);
	//TODO Apply damage.
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0){
		PlayDeath();
	}
}

void ASwordCombatCharacter::ResetCharacter(){
	bGotHit = false;
	bIsReadyToAttack = true;
}

void ASwordCombatCharacter::PlayDeath(){
	bIsDeath = true;
	DisableInput(GetController()->CastToPlayerController());
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(OUT Handle, this, &ASwordCombatCharacter::DisableFromWorld, 2, false);
}

void ASwordCombatCharacter::DisableFromWorld(){
	SetActorEnableCollision(false);
}
