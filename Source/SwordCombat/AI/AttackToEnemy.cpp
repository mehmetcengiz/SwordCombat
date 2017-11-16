// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackToEnemy.h"
#include "SwordCombat.h"
#include "SwordCombatAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SwordCombatCharacter.h"


EBTNodeResult::Type UAttackToEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	
	//Get SwordCombat AI Controller.
	auto ControlledAI = OwnerComp.GetAIOwner();
	if (!ensure(ControlledAI)) { return EBTNodeResult::Failed; }
	auto SwordCombatAI = Cast<ASwordCombatAIController>(ControlledAI);
	if (!ensure(SwordCombatAI)) { return EBTNodeResult::Failed; }

	
	SwordCombatAI->PrimaryAttack();
	return EBTNodeResult::Type::Succeeded;
}
