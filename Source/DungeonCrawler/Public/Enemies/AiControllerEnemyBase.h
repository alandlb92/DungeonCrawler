// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AiControllerEnemyBase.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API AAiControllerEnemyBase : public AAIController
{
	GENERATED_BODY()
public:
	AAiControllerEnemyBase(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BTC;


	UPROPERTY(transient)
	class UBlackboardComponent* BBC;

	FBlackboard::FKey EnemyKeyId;
};
