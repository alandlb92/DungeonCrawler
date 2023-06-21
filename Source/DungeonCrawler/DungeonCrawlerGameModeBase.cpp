// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonCrawlerGameModeBase.h"

void ADungeonCrawlerGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // Coloque o código para habilitar o cursor do mouse aqui
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->bShowMouseCursor = true;

    // Outras configurações, se necessário
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;
    PlayerController->SetInputMode(FInputModeGameAndUI());
}
