// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HUDWidget.h"
#include "Components/ProgressBar.h"

void UHUDWidget::UpdateHpBar(float hpPercentage)
{
	_hpBar->SetPercent(hpPercentage);
}
