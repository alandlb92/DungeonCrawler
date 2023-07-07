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

void UCharacterAnimInstanceBase::SkillHitFrameStart()
{
	OnSkillHitFrameStart.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::SkillHitFrameEnd()
{
	OnSkillHitFrameEnd.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::SecondaryHitFrameStart()
{
	OnSecondaryHitFrameStart.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::SecondaryHitFrameEnd()
{
	OnSecondaryHitFrameEnd.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::AdjustRotation()
{
	OnAdjustRotationBetweenAnimEvent.ExecuteIfBound();
}

void UCharacterAnimInstanceBase::ChangeCharacterState(CharacterState state)
{
	OnChangeCharacterState.Execute(state);
}
