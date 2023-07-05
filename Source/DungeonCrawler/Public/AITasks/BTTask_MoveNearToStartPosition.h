// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveNearToStartPosition.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UBTTask_MoveNearToStartPosition : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_MoveNearToStartPosition(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _startPositionDistance = 100;

private:
	class AEnemyCharacter* _characterOwner;
	FVector GetRandomPosition(FVector center, float radioDistance);
};
