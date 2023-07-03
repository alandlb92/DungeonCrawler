// Copyright Epic Games, Inc. All Rights Reserved.


#include "DungeonCrawlerGameModeBase.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

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
		if (!_gameOverWidgetInstance) {
			_gameOverWidgetInstance = CreateWidget<UGameOverWidget>(GetWorld(), _gameOverWidget);
		}

		if (_gameOverWidgetInstance) {
			_gameOverWidgetInstance->AddToViewport(1000);
			_gameOverWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
			

			ClickGameOverButton quit;
			quit.BindUObject(this, &ADungeonCrawlerGameModeBase::Quit);
			ClickGameOverButton continuePlay;
			continuePlay.BindUObject(this, &ADungeonCrawlerGameModeBase::ContinuePlaying);
			_gameOverWidgetInstance->Configure(quit, continuePlay);
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
	APlayerCharacter* player = Cast<APlayerCharacter>(_playerController->GetCharacter());
	player->DisableGameplayInput();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			if (_gameOverWidgetInstance)
				_gameOverWidgetInstance->Open();
		}, 4, false);

}

void ADungeonCrawlerGameModeBase::ContinuePlaying()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ADungeonCrawlerGameModeBase::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), _playerController, EQuitPreference::Quit, false);
}
