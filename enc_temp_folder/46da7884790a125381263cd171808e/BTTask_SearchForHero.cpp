// Fill out your copyright notice in the Description page of Project Settings.


#include "AITasks/BTTask_SearchForHero.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyCharacter.h"
#include "Enemies/AiControllerEnemyBase.h"
#include "Player/PlayerCharacter.h"

UBTTask_SearchForHero::UBTTask_SearchForHero(const FObjectInitializer& ObjectInitializer)
{
	bCreateNodeInstance = true;
	NodeName = "Search for a hero";
}

EBTNodeResult::Type UBTTask_SearchForHero::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!_target)
		_target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Hero"));

	if(!_playerCharacter)
		_playerCharacter = Cast<APlayerCharacter>(_target);

	if (!_characterOwner) {

		AAiControllerEnemyBase* aic = Cast<AAiControllerEnemyBase>(OwnerComp.GetOwner());
		if (aic)
		{
			_characterOwner = Cast<AEnemyCharacter>(aic->GetCharacter());
		}
	}


	if (_target && _characterOwner)
	{
		if (_characterOwner)
		{
			float distance = FVector::Distance(_characterOwner->GetActorLocation(), _target->GetActorLocation());

			if (_playerCharacter->IsDie())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", EnemyAIState::EAIWAITINGFORAPPROACH);
			}
			if (distance > _characterOwner->_distanceToStartChasing)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", EnemyAIState::EAIWAITINGFORAPPROACH);			
			}
			else if (distance <= _characterOwner->_distanceToStartChasing && distance > _characterOwner->_distanceToInteract)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", EnemyAIState::EAICHASING);
			}
			else if (distance <= _characterOwner->_distanceToInteract)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("EnemyState", EnemyAIState::EAIATTACKING);
			}
		}
	}
	else
	{
		AActor* act = _characterOwner->GetWorld()->GetFirstPlayerController()->GetCharacter();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("Hero", act);
		if(act)
			UE_LOG(LogTemp, Warning, TEXT("Hero found"))
	}

	return EBTNodeResult::Type::Succeeded;
}
