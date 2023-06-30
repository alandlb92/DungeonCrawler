// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base/CharacterStats.h"
#include "CharacterBase.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	ACharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	class UCharacterMovementComponent* _movementComponent;

	CharacterStats* _stats;
	UPROPERTY()
	class UCharacterAnimInstanceBase* _anim;
	UPROPERTY()
	class UDamageComponent* _damageComp;
	UPROPERTY()
	class UAttackComponent* _attackComp;
	UFUNCTION()
	void LookAt(AActor* toLook);
	UFUNCTION()
	virtual void OnDie();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _distanceToInteract = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAttributesData* _attributes;

	bool IsDie();

};
