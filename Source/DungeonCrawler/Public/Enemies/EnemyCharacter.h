// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base/CharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
	float _distanceToStartChasing = 500;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* _behaviourTree;
};
