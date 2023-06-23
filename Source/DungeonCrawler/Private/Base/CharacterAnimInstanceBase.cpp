// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CharacterAnimInstanceBase.h"

void UCharacterAnimInstanceBase::HitFrameStart()
{
	OnHitFrameStart.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::HitFrameEnd()
{
	OnHitFrameEnd.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::ChangeCharacterState(CharacterState state)
{
	OnChangeCharacterState.Execute(state);
}
