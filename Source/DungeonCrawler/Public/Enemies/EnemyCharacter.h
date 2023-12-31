// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base/CharacterBase.h"
#include "Collectables/Collectable.h"
#include <Player/DGPlayerState.h>
#include "EnemyCharacter.generated.h"



UENUM(BlueprintType)
enum EnemyAIState : uint8
{
	EAIWAITINGFORAPPROACH UMETA(DisplayName = "WAITINGFORAPPROACH"),
	EAICHASING UMETA(DisplayName = "CHASING"),
	EAIATTACKING UMETA(DisplayName = "ATTACKING"),
	EAIDEAD UMETA(DisplayName = "DEAD")
};

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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ACollectable> _healOrb;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ACollectable> _boostAttackOrb;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ACollectable> _boostDefenseOrb;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TSubclassOf<ACollectable> _boostSpeedOrb;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
		float _distanceToStartChasing = 500;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* _behaviourTree;

	bool _attack;

	CharacterState characterState;

	virtual void OnDie() override;

	FVector _startPosition;

private:

	AActor* _hero;

	void ChangeCharacterState(CharacterState state);
	void AdjustRotation();

	void DropHealOrb();
	void DropRandomBoostOrNothing();
	FTransform GetSpawnTransform();
};
