// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnimInstance.h"

void UPlayerAnimInstance::HitFrame()
{
	UE_LOG(LogTemp, Warning, TEXT("HitFrame"));
}

void UPlayerAnimInstance::ChangeCharacterState(CharacterState state)
{
	OnChangeCharacterState.Execute(state);
}
