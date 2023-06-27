// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttackComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DamageComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	_boxCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (!_boxCollision)
	{
		UE_LOG(LogTemp, Error, TEXT("UBoxComponent NOT FOUND on %s"), *GetOwner()->GetName());
	}
	else
	{
		_boxCollision->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnOverlapBegin);
		DisableHitBox();
	}
	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackComponent::EnableHitBox()
{
	if (_boxCollision)
		_boxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UAttackComponent::DisableHitBox()
{
	if (_boxCollision)
		_boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

									 
void UAttackComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() == OtherActor)
		return;

	UE_LOG(LogTemp, Error, TEXT("TODO calculate damage"), *GetOwner()->GetName());

	UDamageComponent* damageComp = OtherActor->GetComponentByClass<UDamageComponent>();
	if (damageComp)
		damageComp->TakeDamage(10);
}


