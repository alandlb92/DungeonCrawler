// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "NavigationSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/MouseHelper.h"


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

	FVector input = FVector(RotatedX, RotatedY, 0);
	input = _springArm->GetRelativeRotation().RotateVector(input);
	AddInputVector(input);
}


void UPlayerCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CanMove && Velocity.Length() > 0) {
		StopMovementImmediately();
	}
}

