// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/WrapBox.h"
#include "HUDWidget.generated.h"



UCLASS()
class DUNGEONCRAWLER_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Configure();

	UFUNCTION()
	void UpdateSkillCountDown(float percent);

	UFUNCTION()
	void UpdateHpBar(float hpPercentage, float value, FColor color);

	UFUNCTION()
	void UpdateAttackBoostCountDown(float countDown);
	UFUNCTION()
	void UpdateDefenseBoostCountDown(float countDown);
	UFUNCTION()
	void UpdateSpeedBoostCountDown(float countDown);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* _hpBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* _skillBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _attackBoostCountDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWrapBox* _attackBoostBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _defenseBoostCountDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWrapBox* _defenseBoostBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* _speedBoostCountDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWrapBox* _speedBoostBox;

};
