// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "CharacterInWorldWidget.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API UCharacterInWorldWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void RunChangeHpEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _feedBackText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* _hpBar;

	void UpdateHpBar(float hpPercentage, float value, FColor color);
};
