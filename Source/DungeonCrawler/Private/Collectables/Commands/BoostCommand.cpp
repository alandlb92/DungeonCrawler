// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/Commands/BoostCommand.h"


void UBoostCommand::Execute()
{
	Super::Execute();

	if (_player)	
	{
		switch (_boostType)
		{
		case BSPEED:
			_player->GetStats()->AddTempBoostSpeed(_boostPower, _boostTime);
			break;
		case BATTACK:
			_player->GetStats()->AddTempBoostAttack(_boostPower, _boostTime);
			break;
		case BDEFENSE:
			_player->GetStats()->AddTempBoostDefense(_boostPower, _boostTime);
			break;
		default:
			break;
		}

	}
}