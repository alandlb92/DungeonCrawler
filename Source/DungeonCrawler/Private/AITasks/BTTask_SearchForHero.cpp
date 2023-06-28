// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_SearchForHero.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyCharacter.h"

UBTTask_SearchForHero::UBTTask_SearchForHero(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Search for a hero";
}

EBTNodeResult::Type UBTTask_SearchForHero::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(!_target)
		_target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Hero"));

	if (_target)
	{
		if(!_characterOwner)
			_characterOwner = Cast<AEnemyCharacter>(OwnerComp.GetOwner());
		
		if (_characterOwner) {



		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Hero", GetWorld()->GetFirstPlayerController()->GetOwner());
	}

	return EBTNodeResult::Type::Succeeded;
}
