// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_EnemySetAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyCharacter.h"
#include "Enemies/AiControllerEnemyBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_EnemySetAttack::UBTTask_EnemySetAttack(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Set attack";
}

EBTNodeResult::Type UBTTask_EnemySetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (FindReferences(OwnerComp))
	{
		_characterOwner->_attack = enableAttack;
	}

	return EBTNodeResult::Succeeded;
}

bool UBTTask_EnemySetAttack::FindReferences(UBehaviorTreeComponent& OwnerComp)
{
	if (!_target)
		_target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Hero"));

	if (!_characterOwner) {

		_aic = Cast<AAiControllerEnemyBase>(OwnerComp.GetOwner());
		if (_aic)
		{
			_characterOwner = Cast<AEnemyCharacter>(_aic->GetCharacter());
		}
	}

	return _target && _characterOwner;
}
