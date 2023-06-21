// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


void UPlayerCharacterMovementComponent::Configure(UPlayerAnimInstance* anim)
{
	_anim = anim;
	_playerController = GetWorld()->GetFirstPlayerController();
}

void UPlayerCharacterMovementComponent::MoveToMousePosition()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveToMousePosition"));
	if (_playerController)
	{
		FHitResult hit = RaycastFromMouse(_playerController);
		
		if (hit.HasValidHitObjectHandle())
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(_playerController, hit.ImpactPoint);
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("_playerController is null"));
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
