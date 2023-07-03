// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/Widgets/GameOverWidget.h"
#include "DungeonCrawlerGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UGameOverWidget> _gameOverWidget;
	UGameOverWidget* _gameOverWidgetInstance;
private:
	APlayerController* _playerController;
	void GameOver();

	void ContinuePlaying();
	void Quit();
};
