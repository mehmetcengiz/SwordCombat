// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractState.h"

void UInteractState::OnRightButtonPressed() {
	Super::OnRightButtonPressed();
	UE_LOG(LogTemp, Warning, TEXT("InteractState> OnRightButtonPressed."));
}


