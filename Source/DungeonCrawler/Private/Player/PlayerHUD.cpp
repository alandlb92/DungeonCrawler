// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerHUD.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("APlayerHUD::BeginPlay"));

	if (_widget)
	{
		if (!_widgetInstance)
			_widgetInstance = CreateWidget<UHUDWidget>(GetWorld(), _widget);

		if (_widgetInstance)
			_widgetInstance->AddToViewport();
	}
}
