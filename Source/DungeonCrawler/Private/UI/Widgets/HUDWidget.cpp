// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HUDWidget.h"

void UHUDWidget::Configure()
{
	_attackBoostBox->SetVisibility(ESlateVisibility::Collapsed);
	_defenseBoostBox->SetVisibility(ESlateVisibility::Collapsed);
	_speedBoostBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UHUDWidget::UpdateSkillCountDown(float percent)
{
	_skillBar->SetPercent(percent);
}

void UHUDWidget::UpdateHpBar(float hpPercentage, float value, FColor color)
{
	_hpBar->SetPercent(hpPercentage);
}

void UHUDWidget::UpdateAttackBoostCountDown(float countDown)
{
	if (countDown > 0)
	{
		if (_attackBoostBox->Visibility == ESlateVisibility::Collapsed)
			_attackBoostBox->SetVisibility(ESlateVisibility::Visible);

		FNumberFormattingOptions format = FNumberFormattingOptions();
		format.MaximumFractionalDigits = 0;
		_attackBoostCountDown->SetText(FText::AsNumber(countDown, &format));
	}
	else
	{
		_attackBoostBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UHUDWidget::UpdateDefenseBoostCountDown(float countDown)
{
	if (countDown > 0)
	{
		if (_defenseBoostBox->Visibility == ESlateVisibility::Collapsed)
			_defenseBoostBox->SetVisibility(ESlateVisibility::Visible);

		FNumberFormattingOptions format = FNumberFormattingOptions();
		format.MaximumFractionalDigits = 0;
		_defenseBoostCountDown->SetText(FText::AsNumber(countDown, &format));
	}
	else
	{
		_defenseBoostBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UHUDWidget::UpdateSpeedBoostCountDown(float countDown)
{
	if (countDown > 0)
	{
		if (_speedBoostBox->Visibility == ESlateVisibility::Collapsed)
			_speedBoostBox->SetVisibility(ESlateVisibility::Visible);

		FNumberFormattingOptions format = FNumberFormattingOptions();
		format.MaximumFractionalDigits = 0;
		_speedBoostCountDown->SetText(FText::AsNumber(countDown, &format));
	}
	else
	{
		_speedBoostBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}