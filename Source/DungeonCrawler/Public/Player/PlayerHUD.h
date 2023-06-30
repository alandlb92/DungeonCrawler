// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/HUDWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UHUDWidget> _widget;
	UHUDWidget* _widgetInstance;	
};
