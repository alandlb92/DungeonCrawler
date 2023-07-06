// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UPlayerCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

private:
		UPROPERTY()
		class USpringArmComponent* _springArm;

public:
	void Configure(USpringArmComponent* camera, APlayerController* playerController);
	void MoveToPosition(FVector destination);
	void MoveToActor(AActor* actor);
	void MoveToMouseDirection();
	bool CanMove;

private:
	APlayerController* _playerController;

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
