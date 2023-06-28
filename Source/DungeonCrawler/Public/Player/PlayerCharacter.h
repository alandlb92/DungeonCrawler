// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/AttributesData.h"
#include "Base/CharacterBase.h"
#include "PlayerCharacter.generated.h"

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

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnableGameplayInput();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* _springArm;

private:

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
	class UPlayerCharacterMovementComponent* _movementComponent;
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
};
