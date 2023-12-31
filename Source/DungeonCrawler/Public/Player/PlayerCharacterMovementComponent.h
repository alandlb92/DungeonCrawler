// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacterMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FJoystickInput
{
	GENERATED_BODY()
public:
	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	FVector2D MovementInput;

private:
	FVector2D RawMovementInput;
};


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

	void InputDirectionX(float inputX);
	void InputDirectionY(float inputY);

private:
	APlayerController* _playerController;
	UPROPERTY()
	FJoystickInput _joystickInput;
	void AddInput(FVector2D input);

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
