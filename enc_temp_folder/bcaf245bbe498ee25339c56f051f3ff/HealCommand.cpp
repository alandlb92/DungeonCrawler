// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/Commands/HealCommand.h"

void UHealCommand::Execute()
{
	Super::Execute();
	if (_player)
	{
		_player->GetStats()->Heal(_healPower);
	}
}
