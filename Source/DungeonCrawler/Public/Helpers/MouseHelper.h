// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DUNGEONCRAWLER_API MouseHelper
{
public:
	static FHitResult RaycastFromMouse(APlayerController* PlayerController, float RayLength = 10000.f);
	static FVector2D GetMousePositionFromCenterOrigin();
};
