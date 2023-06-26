// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/MouseHelper.h"

FHitResult MouseHelper::RaycastFromMouse(APlayerController* PlayerController, float RayLength)
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

FVector2D MouseHelper::GetMousePositionFromCenterOrigin()
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