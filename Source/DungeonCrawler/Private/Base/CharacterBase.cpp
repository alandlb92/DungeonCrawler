// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AttackComponent.h"
#include "Components/DamageComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Base/CharacterAnimInstanceBase.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	_movementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (!_movementComponent)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the MovementComponent"));


	DieEvent onDie;
	onDie.BindUObject(this, &ACharacterBase::OnDie);
	_stats = new CharacterStats(_attributes, onDie);	

	_anim = Cast<UCharacterAnimInstanceBase>(GetMesh()->GetAnimInstance());
	if (!_anim)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UCharacterAnimInstanceBase"));

	_damageComp = FindComponentByClass<UDamageComponent>();
	if (!_damageComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UDamageComponent"));
	}
	else
		_damageComp->Configure(_attributes, _stats);

	_attackComp = FindComponentByClass<UAttackComponent>();
	if (!_attackComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UAttackComponent"));
	}
	else
		_attackComp->Configure(_attributes, _stats);

	if (_attackComp && _anim)
	{
		_anim->OnHitFrameStart.BindUObject(_attackComp, &UAttackComponent::EnableHitBox);
		_anim->OnHitFrameEnd.BindUObject(_attackComp, &UAttackComponent::DisableHitBox);

		_anim->OnSecondaryHitFrameStart.BindUObject(_attackComp, &UAttackComponent::EnableSecondaryHitBox);
		_anim->OnSecondaryHitFrameEnd.BindUObject(_attackComp, &UAttackComponent::DisableSecondaryHitBox);
	}

}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_movementComponent->Velocity.Length() > 0)
		_anim->_velocityScale = (_movementComponent->Velocity.Length() / _movementComponent->MaxWalkSpeed) * 100;
	else
		_anim->_velocityScale = 0;
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ACharacterBase::LookAt(AActor* toLook)
{
	FRotator lookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), toLook->GetActorLocation());
	SetActorRotation(lookAtRotator.Quaternion());
}

void ACharacterBase::OnDie()
{
	_anim->_die = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
	{
		this->Destroy();
	}, 3, false);
}