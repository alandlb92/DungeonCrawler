// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/DGPlayerState.h"
#include "CharacterAnimInstanceBase.generated.h"

DECLARE_DELEGATE_OneParam(ChangeCharacterStateEvent, CharacterState);
DECLARE_DELEGATE(HitFrameEvent);
/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API UCharacterAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	ChangeCharacterStateEvent OnChangeCharacterState;
	HitFrameEvent OnHitFrameStart;
	HitFrameEvent OnHitFrameEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	float _velocityScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	bool _attack;
	
	UFUNCTION(BlueprintCallable)
	void HitFrameStart();
	UFUNCTION(BlueprintCallable)
	void HitFrameEnd();
	


	UFUNCTION(BlueprintCallable)
	void ChangeCharacterState(CharacterState state);
	
};
