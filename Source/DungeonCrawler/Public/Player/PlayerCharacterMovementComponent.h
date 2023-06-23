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
		class UPlayerAnimInstance* _anim;
		UPROPERTY()
		class USpringArmComponent* _springArm;

public:
	void Configure(UPlayerAnimInstance* anim, USpringArmComponent* camera);
	void MoveToMousePosition();
	void MoveToMouseDirection();
	bool CanMove;

private:
	APlayerController* _playerController;
	FHitResult RaycastFromMouse(APlayerController* PlayerController, float RayLength = 10000.f);
	FVector2D GetMousePositionFromCenterOrigin();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
