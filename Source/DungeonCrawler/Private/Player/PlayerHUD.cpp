// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerHUD.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (_widget)
	{
		if (!_widgetInstance)
			_widgetInstance = CreateWidget<UHUDWidget>(GetWorld(), _widget);

		if (_widgetInstance) {
			_widgetInstance->AddToViewport();
			_widgetInstance->Configure();
		}
	}


}
