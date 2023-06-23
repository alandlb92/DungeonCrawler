// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "NavigationSystem.h"
#include "GameFramework/SpringArmComponent.h"


void UPlayerCharacterMovementComponent::Configure(UCharacterAnimInstanceBase* anim, USpringArmComponent* springArm)
{
	_anim = anim;
	_springArm = springArm;
	_playerController = GetWorld()->GetFirstPlayerController();
}

void UPlayerCharacterMovementComponent::MoveToMousePosition()
{
	if (!CanMove)
		return;

	UE_LOG(LogTemp, Warning, TEXT("MoveToMousePosition"));
	if (_playerController)
	{
		FHitResult hit = RaycastFromMouse(_playerController);

		if (hit.HasValidHitObjectHandle())
		{
			FVector destination = hit.ImpactPoint;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(_playerController, destination);
		}
		else
			UE_LOG(LogTemp, Error, TEXT("hit.HasValidHitObjectHandle()"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("_playerController is null"));
}

void UPlayerCharacterMovementComponent::MoveToMouseDirection()
{
	if (!CanMove)
		return;

	FVector2D inputToFixRotation = GetMousePositionFromCenterOrigin();
	float AngleInRadians = FMath::DegreesToRadians(90.0f);
	float CosTheta = FMath::Cos(AngleInRadians);
	float SinTheta = FMath::Sin(AngleInRadians);

	float RotatedX = inputToFixRotation.X * CosTheta - inputToFixRotation.Y * SinTheta;
	float RotatedY = inputToFixRotation.X * SinTheta + inputToFixRotation.Y * CosTheta;

	FVector input = FVector(RotatedX, RotatedY, 0);

	UE_LOG(LogTemp, Warning, TEXT("input direction x: %f y: %f z: %f"), input.X, input.Y, input.Z);
	input = _springArm->GetRelativeRotation().RotateVector(input);


	AddInputVector(input);
}



void UPlayerCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!_anim)
		return;

	if (!CanMove && Velocity.Length() > 0) {
		StopMovementImmediately();
	}

	if (Velocity.Length() > 0)
		_anim->_velocityScale = (Velocity.Length() / MaxWalkSpeed) * 100;
	else
		_anim->_velocityScale = 0;
}

FHitResult UPlayerCharacterMovementComponent::RaycastFromMouse(APlayerController* PlayerController, float RayLength)
{

	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("MouseRaycast")), true, PlayerController);
	PlayerController->GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, WorldLocation + (WorldDirection * RayLength), ECC_Visibility, TraceParams);

	return HitResult;
}

FVector2D UPlayerCharacterMovementComponent::GetMousePositionFromCenterOrigin()
{

	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	FVector2D ViewportSize;
	FVector2D MousePosition;

	if (ViewportClient != nullptr)
	{
		ViewportClient->GetViewportSize(ViewportSize);
		ViewportClient->GetMousePosition(MousePosition);
	}

	FVector2D MouseOffset = MousePosition - ViewportSize / 2;

	return MouseOffset;
}