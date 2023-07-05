// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_MoveNearToStartPosition.h"
#include "Enemies/AiControllerEnemyBase.h"
#include "Enemies/EnemyCharacter.h"

UBTTask_MoveNearToStartPosition::UBTTask_MoveNearToStartPosition(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Move near to start position";
}

EBTNodeResult::Type UBTTask_MoveNearToStartPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!_characterOwner) {

		AAiControllerEnemyBase* _aic = Cast<AAiControllerEnemyBase>(OwnerComp.GetOwner());
		if (_aic)
		{
			_characterOwner = Cast<AEnemyCharacter>(_aic->GetCharacter());
		}
	}

	if (_characterOwner)
	{
		OwnerComp.GetBlackboardComponent()
			->SetValueAsVector("NewPosition", GetRandomPosition(_characterOwner->_startPosition, _startPositionDistance));
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

FVector UBTTask_MoveNearToStartPosition::GetRandomPosition(FVector center, float radioDistance)
{
	float xCenter = center.X;
	float yCenter = center.Y;


	float x = FMath::FRandRange(xCenter - radioDistance, xCenter + radioDistance);
	float y = FMath::FRandRange(yCenter - radioDistance, yCenter + radioDistance);

	return FVector(x, y, center.Z);
}
