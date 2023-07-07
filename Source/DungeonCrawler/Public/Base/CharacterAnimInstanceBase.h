
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/DGPlayerState.h"
#include "CharacterAnimInstanceBase.generated.h"

DECLARE_DELEGATE_OneParam(ChangeCharacterStateEvent, CharacterState);
DECLARE_DELEGATE(HitFrameEvent);
DECLARE_DELEGATE(AdjustRotationEvent);
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
	HitFrameEvent OnSecondaryHitFrameStart;
	HitFrameEvent OnSecondaryHitFrameEnd;
	HitFrameEvent OnSkillHitFrameStart;
	HitFrameEvent OnSkillHitFrameEnd;
	AdjustRotationEvent OnAdjustRotationBetweenAnimEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	float _velocityScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	float _attackRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	bool _attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	bool _die;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Animation Variables")
	bool _useSkill;

	UFUNCTION(BlueprintCallable)
	void HitFrameStart();
	UFUNCTION(BlueprintCallable)
	void HitFrameEnd();


	UFUNCTION(BlueprintCallable)
	void SkillHitFrameStart();
	UFUNCTION(BlueprintCallable)
	void SkillHitFrameEnd();

	UFUNCTION(BlueprintCallable)
	void SecondaryHitFrameStart();
	UFUNCTION(BlueprintCallable)
	void SecondaryHitFrameEnd();


	UFUNCTION(BlueprintCallable)
	void AdjustRotation();

	UFUNCTION(BlueprintCallable)
	void ChangeCharacterState(CharacterState state);
};
