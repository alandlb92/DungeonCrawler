// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonCrawlerGameModeBase.h"
#include "Player/PlayerCharacter.h"

void ADungeonCrawlerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Coloque o código para habilitar o cursor do mouse aqui
	_playerController = GetWorld()->GetFirstPlayerController();
	_playerController->bShowMouseCursor = true;

	// Outras configurações, se necessário
	_playerController->bEnableClickEvents = true;
	_playerController->bEnableMouseOverEvents = true;
	FInputModeGameAndUI inputMode = FInputModeGameAndUI();
	inputMode.SetHideCursorDuringCapture(false);

	_playerController->SetInputMode(inputMode);

	if (_gameOverWidget)
	{
		if (!_gameOverWidgetInstance)
			_gameOverWidgetInstance = CreateWidget<UGameOverWidget>(GetWorld(), _gameOverWidget);

		if (_gameOverWidgetInstance) {
			_gameOverWidgetInstance->AddToViewport();
			_gameOverWidgetInstance->SetRenderOpacity(0);
		}
	}

	APlayerCharacter* player = Cast<APlayerCharacter>(_playerController->GetCharacter());

	if (player) {
		player->_onPlayerDie.BindUObject(this, &ADungeonCrawlerGameModeBase::GameOver);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Player not found"));
}

void ADungeonCrawlerGameModeBase::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver"));

	if (_gameOverWidgetInstance)
		_gameOverWidgetInstance->SetRenderOpacity(1);
}
