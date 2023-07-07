// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "NavigationSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/MouseHelper.h"


void FJoystickInput::Sanitize()
{
	MovementInput = RawMovementInput;
	RawMovementInput.Set(0.0f, 0.0f);
}

void FJoystickInput::MoveX(float AxisValue)
{
	RawMovementInput.Y = AxisValue;
}

void FJoystickInput::MoveY(float AxisValue)
{
	RawMovementInput.X = AxisValue;
}

void UPlayerCharacterMovementComponent::Configure(USpringArmComponent* springArm, APlayerController* playerController)
{
	_springArm = springArm;
	_playerController = playerController;
}

void UPlayerCharacterMovementComponent::MoveToPosition(FVector destination)
{
	if (!CanMove)
		return;

	if (_playerController)
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(_playerController, destination);
	else
		UE_LOG(LogTemp, Error, TEXT("_playerController is null"));
}

void UPlayerCharacterMovementComponent::MoveToActor(AActor* actor)
{
	if (!CanMove)
		return;

	if (_playerController)
		UAIBlueprintHelperLibrary::SimpleMoveToActor(_playerController, actor);
	else
		UE_LOG(LogTemp, Error, TEXT("_playerController is null"));
}

void UPlayerCharacterMovementComponent::MoveToMouseDirection()
{
	if (!CanMove)
		return;

	FVector2D inputToFixRotation = MouseHelper::GetMousePositionFromCenterOrigin();
	float AngleInRadians = FMath::DegreesToRadians(90.0f);
	float CosTheta = FMath::Cos(AngleInRadians);
	float SinTheta = FMath::Sin(AngleInRadians);

	float RotatedX = inputToFixRotation.X * CosTheta - inputToFixRotation.Y * SinTheta;
	float RotatedY = inputToFixRotation.X * SinTheta + inputToFixRotation.Y * CosTheta;

	FVector2d input = FVector2d(RotatedX, RotatedY);
	AddInput(input);
}

void UPlayerCharacterMovementComponent::InputDirectionX(float inputX)
{
	if (!CanMove)
		return;

	_joystickInput.MoveX(inputX);
}

void UPlayerCharacterMovementComponent::InputDirectionY(float inputY)
{
	if (!CanMove)
		return;

	_joystickInput.MoveY(inputY);
}

void UPlayerCharacterMovementComponent::AddInput(FVector2D input)
{
	FVector input3D = FVector(input.X, input.Y, 0);
	input3D = _springArm->GetRelativeRotation().RotateVector(input3D);
	AddInputVector(input3D);
}


void UPlayerCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_joystickInput.Sanitize();
	AddInput(_joystickInput.MovementInput);

	if (!CanMove && Velocity.Length() > 0) {
		StopMovementImmediately();
	}
}

