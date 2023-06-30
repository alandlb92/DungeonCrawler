// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/BaseLevelScriptActor.h"
#include "Player/PlayerCharacter.h"

void ABaseLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ABaseLevelScriptActor::BeginPla"));
}
