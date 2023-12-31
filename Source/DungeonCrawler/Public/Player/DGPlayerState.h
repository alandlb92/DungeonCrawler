
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DGPlayerState.generated.h"


UENUM(BlueprintType)
enum CharacterState : uint8
{
	IDLE UMETA(DisplayName = "IDLE"),
	WALKING UMETA(DisplayName = "Walking"),
	ATTACKING UMETA(DisplayName = "Attacking"),
	DEAD UMETA(DisplayName = "Dead")
};

UCLASS()
class DUNGEONCRAWLER_API ADGPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void ChangeCharacterState(CharacterState state);
	CharacterState GetCharacterState();

private:
	CharacterState _characterState;
};
