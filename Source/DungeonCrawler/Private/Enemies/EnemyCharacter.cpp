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
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_anim) {
		_anim->_attack = _attack;

		if(_attack && _movementComponent->Velocity.Length() > 0)
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

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
	{
		this->Destroy();
	}, 3, false);
}

void AEnemyCharacter::ChangeCharacterState(CharacterState state)
{
	characterState = state;
}

void AEnemyCharacter::AdjustRotation()
{
	LookAt(_hero);
}

