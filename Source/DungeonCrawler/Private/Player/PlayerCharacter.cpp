// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterMovementComponent.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/DGPlayerState.h"
#include "Helpers/MouseHelper.h"
#include "Components/InteractableComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	moveToMousePosition = false;
	IsLeftMouseKeyDown = false;
	IsSpaceBarDown = false;
	IsLeftMouseKeyDownAndOverEnemyToAttack = false;	

	_playerController = GetWorld()->GetFirstPlayerController();
	if (!_playerController)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the PlayerController"));

	_state = Cast<ADGPlayerState>(GetPlayerState());
	if (!_state)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the ADGPlayerState"));

	if (_anim && _state)
		_anim->OnChangeCharacterState.BindUObject(_state, &ADGPlayerState::ChangeCharacterState);

	_springArm = FindComponentByClass<USpringArmComponent>();
	if (!_springArm)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the USpringArmComponent"));
	

	_movementComponent = Cast<UPlayerCharacterMovementComponent>(GetMovementComponent());
	if (_movementComponent) {
		_movementComponent->Configure(_anim, _springArm, _playerController);
		EnableGameplayInput();
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the MovementComponent"));


}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_movementComponent->CanMove = _state->GetCharacterState() != ATTACKING;

	if (moveToMousePosition)
		_movementComponent->MoveToMouseDirection();

	if (_anim)
		_anim->_attack = IsSpaceBarDown || IsLeftMouseKeyDownAndOverEnemyToAttack;

	UpdatePlayerState();
	MouseIsDownInteractionLoop();
	WaitDistanceAndInteract();
}

void APlayerCharacter::MouseIsDownInteractionLoop()
{
	if (IsLeftMouseKeyDown)
	{
		FHitResult hit = MouseHelper::RaycastFromMouse(_playerController);
		if (hit.HasValidHitObjectHandle())
		{
			AActor* actorHited = hit.GetActor();

			if (actorHited && actorHited->GetComponentByClass<UInteractableComponent>())
			{
				if (FVector::Distance(actorHited->GetActorLocation(), GetActorLocation()) <= _distanceToInteract)
				{
					LookAt(actorHited);
					IsLeftMouseKeyDownAndOverEnemyToAttack = true;
				}
				else
				{
					IsLeftMouseKeyDownAndOverEnemyToAttack = false;
					_movementComponent->MoveToMouseDirection();
				}
			}
			else
			{
				_movementComponent->MoveToMouseDirection();
			}
		}
	}
	else
	{
		IsLeftMouseKeyDownAndOverEnemyToAttack = false;
	}
}

void APlayerCharacter::UpdatePlayerState()
{
	if (!_state)
		return;

	if (_movementComponent->Velocity.Length() > 0 && _state->GetCharacterState() != ATTACKING)
		_state->ChangeCharacterState(WALKING);
	else if (_state->GetCharacterState() != ATTACKING)
		_state->ChangeCharacterState(IDLE);
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::EnableGameplayInput()
{
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCharacter::LeftMouseKeyDown);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APlayerCharacter::LeftMouseKeyUp);

	InputComponent->BindAction("RegularAttack", IE_Pressed, this, &APlayerCharacter::SpaceBarKeyDown);
	InputComponent->BindAction("RegularAttack", IE_Released, this, &APlayerCharacter::SpaceBarKeyUp);
}

void APlayerCharacter::LeftMouseKeyDown()
{
	IsLeftMouseKeyDown = true;
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
	{
		if (!IsLeftMouseKeyDown)
			ClickInteraction();
	}, .1f, false);
}

void APlayerCharacter::LeftMouseKeyUp()
{
	IsLeftMouseKeyDown = false;
}

void APlayerCharacter::SpaceBarKeyDown()
{
	IsSpaceBarDown = true;
}

void APlayerCharacter::SpaceBarKeyUp()
{
	IsSpaceBarDown = false;
}

void APlayerCharacter::ClickInteraction()
{
	FHitResult hit = MouseHelper::RaycastFromMouse(_playerController);
	if (hit.HasValidHitObjectHandle())
	{
		if (hit.GetActor()->GetComponentByClass<UInteractableComponent>()) {
			_actorToInteract = hit.GetActor();
			_movementComponent->MoveToActor(_actorToInteract);
		}
		else {
			_movementComponent->MoveToPosition(hit.ImpactPoint);
			ShowMouseMovementFeedBack();
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("hit.HasValidHitObjectHandle()"));
}

void APlayerCharacter::EnableMoveToMouse()
{
	moveToMousePosition = true;
}

void APlayerCharacter::DisableMoveToMouse()
{
	moveToMousePosition = false;
}

void APlayerCharacter::WaitDistanceAndInteract()
{
	if (_actorToInteract)
	{
		if (FVector::Distance(_actorToInteract->GetActorLocation(), GetActorLocation()) <= _distanceToInteract) {
			_movementComponent->StopMovementImmediately();
			LookAt(_actorToInteract);
			IsLeftMouseKeyDownAndOverEnemyToAttack = true;
			_actorToInteract = nullptr;
		}
	}
}


void APlayerCharacter::ShowMouseMovementFeedBack()
{
	UE_LOG(LogTemp, Error, TEXT("TODO ShowMouseMovementFeedBack"));
}



