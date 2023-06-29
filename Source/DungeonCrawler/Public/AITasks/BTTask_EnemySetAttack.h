// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemySetAttack.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UBTTask_EnemySetAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_EnemySetAttack(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool enableAttack;

private:
	class AEnemyCharacter* _characterOwner;
	class AActor* _target;
	class AAiControllerEnemyBase* _aic;

	bool FindReferences(UBehaviorTreeComponent& OwnerComp);
	
};
