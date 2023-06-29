// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_EnemyMoveTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyCharacter.h"
#include "Enemies/AiControllerEnemyBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_EnemyMoveTo::UBTTask_EnemyMoveTo(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Chaise Hero";
}

EBTNodeResult::Type UBTTask_EnemyMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (FindReferences(OwnerComp))
	{
		if (_characterOwner->characterState != ATTACKING)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(_aic, _target);
		}
		else
		{
			_characterOwner->GetMovementComponent()->StopMovementImmediately();
		}
	}

	return EBTNodeResult::Succeeded;
}

bool UBTTask_EnemyMoveTo::FindReferences(UBehaviorTreeComponent& OwnerComp)
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
