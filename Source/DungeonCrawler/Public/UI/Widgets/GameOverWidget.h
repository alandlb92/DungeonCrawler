
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameOverWidget.generated.h"

DECLARE_DELEGATE(ClickGameOverButton)

UCLASS()
class DUNGEONCRAWLER_API UGameOverWidget : public UUserWidget
{



	GENERATED_BODY()
public:
	void Configure(ClickGameOverButton quitEvent, ClickGameOverButton continueEvent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor _hoveredColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor _normalColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor _pressedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* _continueButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* _quitButton;

	UFUNCTION(BlueprintImplementableEvent)
	void RunOpenAnimation();

	void Open();

private:
	ClickGameOverButton OnQuitEvent;
	ClickGameOverButton OnContinueEvent;

	UFUNCTION()
	void ClickQuitButton();
	UFUNCTION()
	void ClickContinueButton();

	UFUNCTION()
	void HoverContinue();
	UFUNCTION()
	void UnhoverContinue();
	UFUNCTION()
	void HoverQuit();
	UFUNCTION()
	void UnhoverQuit();
};
