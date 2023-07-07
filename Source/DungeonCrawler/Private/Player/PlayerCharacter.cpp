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
#include "Player/PlayerHUD.h"
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

	if (_anim) {
		_anim->OnSkillHitFrameStart.BindUObject(this, &APlayerCharacter::EnableSkillCollision);
		_anim->OnSkillHitFrameEnd.BindUObject(this, &APlayerCharacter::DisableSkillCollision);
	}


	_springArm = FindComponentByClass<USpringArmComponent>();
	if (!_springArm)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the USpringArmComponent"));


	_playerMovementComponent = Cast<UPlayerCharacterMovementComponent>(GetMovementComponent());
	if (_playerMovementComponent) {
		_playerMovementComponent->Configure(_springArm, _playerController);
		EnableGameplayInput();
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the MovementComponent"));

	HUD = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (HUD)
	{
		_stats->_onChangeHp.AddUObject(HUD->_widgetInstance, &UHUDWidget::UpdateHpBar);
		_stats->_onNotifyTempSpeedBoostTime.AddUObject(HUD->_widgetInstance, &UHUDWidget::UpdateSpeedBoostCountDown);
		_stats->_onNotifyTempAttackBoostTime.AddUObject(HUD->_widgetInstance, &UHUDWidget::UpdateAttackBoostCountDown);
		_stats->_onNotifyTempDefenseBoostTime.AddUObject(HUD->_widgetInstance, &UHUDWidget::UpdateDefenseBoostCountDown);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the PlayerHUD"));

	GetSkillColliderReference();
}

void APlayerCharacter::OnDie()
{
	Super::OnDie();
	_state->ChangeCharacterState(CharacterState::DEAD);
	_onPlayerDie.ExecuteIfBound();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_playerMovementComponent->CanMove = _state->GetCharacterState() != ATTACKING;

	if (moveToMousePosition)
		_playerMovementComponent->MoveToMouseDirection();

	if (_anim)
		_anim->_attack = IsSpaceBarDown || IsLeftMouseKeyDownAndOverEnemyToAttack;

	UpdatePlayerState();
	MouseIsDownInteractionLoop();
	WaitDistanceAndInteract();
	SkillCountDown(DeltaTime);
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
					_playerMovementComponent->MoveToMouseDirection();
				}
			}
			else
			{
				_playerMovementComponent->MoveToMouseDirection();
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

	if (_playerMovementComponent->Velocity.Length() > 0 && _state->GetCharacterState() != ATTACKING)
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
	InputComponent->BindAction("Skill1", IE_Pressed, this, &APlayerCharacter::UseSkill);

	//Joystick
	InputComponent->BindAxis("MovementY", _playerMovementComponent, &UPlayerCharacterMovementComponent::InputDirectionY);
	InputComponent->BindAxis("MovementX", _playerMovementComponent, &UPlayerCharacterMovementComponent::InputDirectionX);

	InputComponent->BindAxis("MouseWheel", this, &APlayerCharacter::CameraZoomController);
}

void APlayerCharacter::DisableGameplayInput()
{
	InputComponent->ClearActionBindings();
}

void APlayerCharacter::SkillCountDown(float DeltaTime)
{
	if (_countSkill)
	{
		if (_skillCounter != 0)
		{
			_skillCounter -= DeltaTime;
			if (_skillCounter <= 0) {
				_skillCounter = 0;
				_countSkill = false;
			}

			HUD->_widgetInstance->UpdateSkillCountDown((_skillCounter / _skillTime));
		}
	}
}

void APlayerCharacter::UseSkill()
{
	if (_anim && _skillCounter == 0) {
		_anim->_useSkill = true;
		_skillCounter = _skillTime;
		HUD->_widgetInstance->UpdateSkillCountDown((_skillCounter / _skillTime));
		_countSkill = false;
	}
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
			_playerMovementComponent->MoveToActor(_actorToInteract);
		}
		else {
			_playerMovementComponent->MoveToPosition(hit.ImpactPoint);
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
			_playerMovementComponent->StopMovementImmediately();
			LookAt(_actorToInteract);
			IsLeftMouseKeyDownAndOverEnemyToAttack = true;
			_actorToInteract = nullptr;
		}
	}
}

void APlayerCharacter::CameraZoomController(float zoom)
{
	_springArm->TargetArmLength += (zoom * _zoomCameraVelocity);
	_springArm->TargetArmLength = FMath::Clamp(_springArm->TargetArmLength, _minCameraDistance, _maxCameraDistance);
}

void APlayerCharacter::GetSkillColliderReference()
{

	TArray<UStaticMeshComponent*> FoundComponents;
	GetComponents<UStaticMeshComponent>(FoundComponents);

	for (auto comp : FoundComponents)
	{
		if (comp->ComponentHasTag("SkillCollider"))
			_skillCollider = comp;

		UE_LOG(LogTemp, Error, TEXT("name: %s"), *comp->GetName());
	}

	if (!_skillCollider) {
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UStaticMeshComponent"));
	}
	else {
		DisableSkillCollision();
		_skillCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapSkillBegin);
		HUD->_widgetInstance->UpdateSkillCountDown(0);
	}
}

void APlayerCharacter::EnableSkillCollision()
{
	_skillCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	_skillCollider->SetVisibility(true);
}

void APlayerCharacter::DisableSkillCollision()
{
	_skillCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_skillCollider->SetVisibility(false);
	_countSkill = true;
}

void APlayerCharacter::ShowMouseMovementFeedBack()
{
	UE_LOG(LogTemp, Error, TEXT("TODO ShowMouseMovementFeedBack"));
}




void APlayerCharacter::OnOverlapSkillBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this == OtherActor)
		return;

	UDamageComponent* damageComp = OtherActor->GetComponentByClass<UDamageComponent>();
	if (damageComp)
		damageComp->TakeDamage(_stats, 4);
}
