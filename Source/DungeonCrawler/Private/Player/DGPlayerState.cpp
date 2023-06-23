// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DGPlayerState.h"

void ADGPlayerState::ChangeCharacterState(CharacterState state)
{
	_characterState = state;
}

CharacterState ADGPlayerState::GetCharacterState()
{
	return _characterState;
}