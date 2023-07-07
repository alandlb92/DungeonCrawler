// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/AttributesData.h"
#include "Base/CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE(PlayerDieEvent)

UCLASS()
class DUNGEONCRAWLER_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnDie() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnableGameplayInput();
	void DisableGameplayInput();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* _springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* _skillCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float _zoomCameraVelocity = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float _maxCameraDistance = 600;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float _minCameraDistance = 400;

	PlayerDieEvent _onPlayerDie;
private:
	float _skillTime = 30;
	float _skillCounter = 0;
	bool _countSkill;
	void SkillCountDown(float DeltaTime);

	UPROPERTY()
	class APlayerHUD* HUD;

	UFUNCTION()
	void UseSkill();

	UPROPERTY()
	class ADGPlayerState* _state;
	UPROPERTY()
	APlayerController* _playerController;
	UPROPERTY()
	AActor* _actorToInteract;

	bool IsLeftMouseKeyDown;
	bool IsSpaceBarDown;
	bool moveToMousePosition;

	bool IsLeftMouseKeyDownAndOverEnemyToAttack;

	UPROPERTY()
	class UPlayerCharacterMovementComponent* _playerMovementComponent;
	void UpdatePlayerState();
	void LeftMouseKeyDown();
	void LeftMouseKeyUp();
	void SpaceBarKeyDown();
	void SpaceBarKeyUp();
	void ClickInteraction();
	void MouseIsDownInteractionLoop();
	void EnableMoveToMouse();	
	void DisableMoveToMouse();
	void ShowMouseMovementFeedBack();	
	void WaitDistanceAndInteract();
	void CameraZoomController(float zoom);
	void GetSkillColliderReference();

	UFUNCTION()
	void EnableSkillCollision();
	UFUNCTION()
	void DisableSkillCollision();
	UFUNCTION()
	void OnOverlapSkillBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
