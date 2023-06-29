// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterVisualizers/CharacterEnemyVisualizer.h"
#include "Components/AttackComponent.h"
#include "Enemies/EnemyCharacter.h"

void FCharacterEnemyVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	const UAttackComponent* AttackComp = Cast<UAttackComponent>(Component);
	const AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Component->GetOwner());

	if (AttackComp && Enemy)
	{
		DrawWireSphere(PDI, Component->GetOwner()->GetActorLocation(), FColor::Red, Enemy->_distanceToStartChasing, 16, SDPG_World);
	
		/*DrawSphere(PDI, Component->GetOwner()->GetActorLocation(), FRotator::ZeroRotator, FVector(Enemy->_distanceToStartChasing),
			3, 3, FMaterial ,1);*/
	}
}
