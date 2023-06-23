// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonCrawlerGameModeBase.h"

void ADungeonCrawlerGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Coloque o c�digo para habilitar o cursor do mouse aqui
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->bShowMouseCursor = true;

    // Outras configura��es, se necess�rio
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;
    FInputModeGameAndUI inputMode = FInputModeGameAndUI();
    inputMode.SetHideCursorDuringCapture(false);

    PlayerController->SetInputMode(inputMode);
}
