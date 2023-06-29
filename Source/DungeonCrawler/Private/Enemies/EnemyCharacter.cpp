// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyCharacter.h"
#include "Base/CharacterAnimInstanceBase.h"

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
	if (_anim)
		_anim->OnChangeCharacterState.BindUObject(this, &AEnemyCharacter::ChangePlayerState);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_anim) {
		_anim->_attack = _attack;
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::ChangePlayerState(CharacterState state)
{
	characterState = state;
}

