// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AiControllerEnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemies/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Player/PlayerCharacter.h"

AAiControllerEnemyBase::AAiControllerEnemyBase(const FObjectInitializer& ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree Component"));
}

void AAiControllerEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_playerCharacter && _characterOwner && BBC)
	{
		BBC->SetValueAsEnum("CharacterState", _characterOwner->characterState);

		float distance = FVector::Distance(_characterOwner->GetActorLocation(), _playerCharacter->GetActorLocation());

		if (_characterOwner->IsDie())
		{
			BBC->SetValueAsEnum("AIState", EnemyAIState::EAIDEAD);
		}
		else if (distance > _characterOwner->_distanceToStartChasing || _playerCharacter->IsDie())
		{
			BBC->SetValueAsEnum("AIState", EnemyAIState::EAIWAITINGFORAPPROACH);
		}
		else if (distance <= _characterOwner->_distanceToStartChasing && distance > _characterOwner->_distanceToInteract)
		{
			BBC->SetValueAsEnum("AIState", EnemyAIState::EAICHASING);
		}
		else if (distance <= _characterOwner->_distanceToInteract)
		{
			BBC->SetValueAsEnum("AIState", EnemyAIState::EAIATTACKING);
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI NOT SET PROPERLY"));
	}
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

void AAiControllerEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	_playerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!_playerCharacter)
		UE_LOG(LogTemp, Error, TEXT("_playerCharacter NOT found"));

	_characterOwner = Cast<AEnemyCharacter>(GetCharacter());
	if (!_characterOwner)
		UE_LOG(LogTemp, Error, TEXT("_characterOwner NOT found"));

	BBC->SetValueAsObject("Hero", _playerCharacter);
}
