// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DGPlayerState.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_DELEGATE_OneParam(ChangeCharacterStateEvent, CharacterState);
/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	ChangeCharacterStateEvent OnChangeCharacterState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	float _velocityScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	bool _attack;
	
	UFUNCTION(BlueprintCallable)
	void HitFrame();
	


	UFUNCTION(BlueprintCallable)
	void ChangeCharacterState(CharacterState state);
	
};
