// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/InWorld/CharacterInWorldWidget.h"

void UCharacterInWorldWidget::UpdateHpBar(float hpPercentage, float value, FColor color)
{
	_feedBackText->SetText(FText::AsNumber(value));
	//_feedBackText->SetColorAndOpacity(FSlateColor(color));
	_hpBar->SetPercent(hpPercentage);
	RunChangeHpEvent();
}