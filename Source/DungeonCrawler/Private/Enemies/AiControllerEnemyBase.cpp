// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AiControllerEnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemies/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAiControllerEnemyBase::AAiControllerEnemyBase(const FObjectInitializer& ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree Component"));
}

void AAiControllerEnemyBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyCharacter* Chr = Cast<AEnemyCharacter>(InPawn);
	if (Chr && Chr->_behaviourTree)
	{
		BBC->InitializeBlackboard(*Chr->_behaviourTree->BlackboardAsset);
		BTC->StartTree(*Chr->_behaviourTree);
	}
}
