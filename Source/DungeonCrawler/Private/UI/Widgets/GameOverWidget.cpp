// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/GameOverWidget.h"

void UGameOverWidget::Configure(ClickGameOverButton quitEvent, ClickGameOverButton continueEvent)
{
	_continueButton->OnHovered.AddDynamic(this, &UGameOverWidget::HoverContinue);
	_continueButton->OnUnhovered.AddDynamic(this, &UGameOverWidget::UnhoverContinue);

	_quitButton->OnHovered.AddDynamic(this, &UGameOverWidget::HoverQuit);
	_quitButton->OnUnhovered.AddDynamic(this, &UGameOverWidget::UnhoverQuit);

	_continueButton->OnClicked.AddDynamic(this, &UGameOverWidget::ClickContinueButton);
	_quitButton->OnClicked.AddDynamic(this, &UGameOverWidget::ClickQuitButton);

	OnQuitEvent = quitEvent;
	OnContinueEvent = continueEvent;
}

void UGameOverWidget::ClickQuitButton()
{
	OnQuitEvent.ExecuteIfBound();
}

void UGameOverWidget::ClickContinueButton()
{
	OnContinueEvent.ExecuteIfBound();
}

void UGameOverWidget::HoverContinue()
{
	_continueButton->SetColorAndOpacity(_hoveredColor);
}

void UGameOverWidget::UnhoverContinue()
{
	_continueButton->SetColorAndOpacity(_normalColor);
}

void UGameOverWidget::HoverQuit()
{
	_quitButton->SetColorAndOpacity(_hoveredColor);
}

void UGameOverWidget::UnhoverQuit()
{
	_quitButton->SetColorAndOpacity(_normalColor);
}

void UGameOverWidget::Open()
{
	SetVisibility(ESlateVisibility::Visible);
	RunOpenAnimation();
}
