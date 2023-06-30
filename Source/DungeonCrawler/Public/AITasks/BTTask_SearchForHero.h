// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemies/EnemyCharacter.h"
#include "BTTask_SearchForHero.generated.h"


UCLASS()
class DUNGEONCRAWLER_API UBTTask_SearchForHero : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SearchForHero(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class AEnemyCharacter* _characterOwner;
	class AActor* _target;
	class APlayerCharacter* _playerCharacter;
};