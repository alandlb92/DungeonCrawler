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

public:
	void Configure(UPlayerAnimInstance* anim);
	void MoveToMousePosition();

private:
	APlayerController* _playerController;
	FHitResult RaycastFromMouse(APlayerController* PlayerController, float RayLength = 10000.f);
	
};
