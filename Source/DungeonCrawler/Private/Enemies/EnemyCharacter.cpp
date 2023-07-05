// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyCharacter.h"
#include "Base/CharacterAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	_hero = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (!_hero)
		UE_LOG(LogTemp, Error, TEXT("hero NOT FOUND"));

	if (_anim) {
		_anim->OnChangeCharacterState.BindUObject(this, &AEnemyCharacter::ChangeCharacterState);
		_anim->OnAdjustRotationBetweenAnimEvent.BindUObject(this, &AEnemyCharacter::AdjustRotation);
	}

	_startPosition = GetActorLocation();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_anim) {
		_anim->_attack = _attack;

		if (_attack && _movementComponent->Velocity.Length() > 0)
			_movementComponent->StopMovementImmediately();
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnDie()
{
	Super::OnDie();

	if (_healOrb)
	{
		FActorSpawnParameters SpawnInfo;
		FTransform SpawnTransform = FTransform::Identity;
		SpawnTransform.SetLocation(GetActorLocation() + (GetActorForwardVector() * -100));
		GetWorld()->SpawnActor<ACollectable>(_healOrb, SpawnTransform, SpawnInfo);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("_healOrb NOT SETED"));
	}

	ChangeCharacterState(CharacterState::DEAD);
	_movementComponent->DisableMovement();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			this->Destroy();
		}, 3, false);
}

void AEnemyCharacter::ChangeCharacterState(CharacterState state)
{
	FString s = "";
	switch (state)
	{
	case IDLE:
		s = "IDLE";
		break;
	case WALKING:
		s = "WALKING";
		break;
	case ATTACKING:
		s = "ATTACKING";
		break;
	case DEAD:
		s = "DEAD";
		break;
	default:
		s = "error";
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Change State: %s"), *s);
	characterState = state;
}

void AEnemyCharacter::AdjustRotation()
{
	if (characterState != DEAD)
		LookAt(_hero);
}

