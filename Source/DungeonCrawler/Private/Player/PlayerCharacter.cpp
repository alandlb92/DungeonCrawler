// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterMovementComponent.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/DGPlayerState.h"
#include "Components/AttackComponent.h"
#include "Components/DamageComponent.h"

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
	canAttack = false;

	_state = Cast<ADGPlayerState>(GetPlayerState());
	if (!_state)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the ADGPlayerState"));

	_anim = Cast<UCharacterAnimInstanceBase>(GetMesh()->GetAnimInstance());
	if (_anim && _state)
		_anim->OnChangeCharacterState.BindUObject(_state, &ADGPlayerState::ChangeCharacterState);
	else
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UCharacterAnimInstanceBase"));


	_springArm = FindComponentByClass<USpringArmComponent>();
	if (!_springArm)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the USpringArmComponent"));


	_damageComp = FindComponentByClass<UDamageComponent>();
	if (!_damageComp)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UDamageComponent"));


	_attackComp = FindComponentByClass<UAttackComponent>();
	if (!_attackComp)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UAttackComponent"));

	if (_attackComp && _anim)
	{
		_anim->OnHitFrameStart.BindUObject(_attackComp, &UAttackComponent::EnableHitBox);
		_anim->OnHitFrameEnd.BindUObject(_attackComp, &UAttackComponent::DisableHitBox);
	}

	_movementComponent = Cast<UPlayerCharacterMovementComponent>(GetMovementComponent());
	if (_movementComponent) {
		_movementComponent->Configure(_anim, _springArm);
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
		_anim->_attack = canAttack;

	UpdatePlayerState();
}


void APlayerCharacter::UpdatePlayerState()
{
	if (!_state)
		return;

	if (_movementComponent->Velocity.Length() > 0 && _state->GetCharacterState() != ATTACKING)
		_state->ChangeCharacterState(WALKING);
	else if(_state->GetCharacterState() != ATTACKING)
		_state->ChangeCharacterState(IDLE);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::EnableGameplayInput()
{
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCharacter::EnableMoveToMouse);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APlayerCharacter::DisableMoveToMouse);
	InputComponent->BindAction("LeftClick", IE_Released, _movementComponent, &UPlayerCharacterMovementComponent::MoveToMousePosition);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APlayerCharacter::ShowMouseMovementFeedBack);

	InputComponent->BindAction("RegularAttack", IE_Pressed, this, &APlayerCharacter::StartRegularAttack);
	InputComponent->BindAction("RegularAttack", IE_Released, this, &APlayerCharacter::EndRegularAttack);
}

void APlayerCharacter::EnableMoveToMouse()
{
	moveToMousePosition = true;
}

void APlayerCharacter::DisableMoveToMouse()
{
	moveToMousePosition = false;
}

void APlayerCharacter::StartRegularAttack()
{
	canAttack = true;
	UE_LOG(LogTemp, Error, TEXT("StartRegularAttack"));
}

void APlayerCharacter::EndRegularAttack()
{
	canAttack = false;
	UE_LOG(LogTemp, Error, TEXT("EndRegularAttack"));
}

void APlayerCharacter::ShowMouseMovementFeedBack()
{
	UE_LOG(LogTemp, Error, TEXT("TODO ShowMouseMovementFeedBack"));
}



