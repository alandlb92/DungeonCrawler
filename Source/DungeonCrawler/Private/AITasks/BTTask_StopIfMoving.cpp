// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_StopIfMoving.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyCharacter.h"
#include "Enemies/AiControllerEnemyBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Tasks/AITask_MoveTo.h"

UBTTask_StopIfMoving::UBTTask_StopIfMoving(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Stop if is moving";
}

EBTNodeResult::Type UBTTask_StopIfMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (FindReferences(OwnerComp))
	{
		if (_characterOwner->GetMovementComponent()->Velocity.Length() > 0)
			_characterOwner->GetMovementComponent()->StopMovementImmediately();
	}

	return EBTNodeResult::Succeeded;
}

bool UBTTask_StopIfMoving::FindReferences(UBehaviorTreeComponent& OwnerComp)
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
