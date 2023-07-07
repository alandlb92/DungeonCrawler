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
}

void UAttackComponent::Configure(CharacterStats* myStats)
{
	_myStats = myStats;
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UBoxComponent*> FoundComponents;
	GetOwner()->GetComponents<UBoxComponent>(FoundComponents);

	for (auto comp : FoundComponents)
	{
		if (comp->ComponentHasTag("HitCollision"))
			_boxCollision1 = comp;
		if (comp->ComponentHasTag("SecondaryHitCollision"))
			_boxCollision2 = comp;
	}

	if (!_boxCollision1)
	{
		UE_LOG(LogTemp, Error, TEXT("UBoxComponent NOT FOUND on %s"), *GetOwner()->GetName());
	}
	else
	{
		_boxCollision1->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnOverlapBegin);
		DisableHitBox();
	}	


	if (!_boxCollision2)
	{
		UE_LOG(LogTemp, Error, TEXT("UBoxComponent NOT FOUND on %s"), *GetOwner()->GetName());
	}
	else
	{
		_boxCollision2->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnOverlapBegin);
		DisableSecondaryHitBox();
	}
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackComponent::EnableHitBox()
{
	if (_boxCollision1)
		_boxCollision1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UAttackComponent::DisableHitBox()
{
	if (_boxCollision1)
		_boxCollision1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UAttackComponent::EnableSecondaryHitBox()
{
	if (_boxCollision2)
		_boxCollision2->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UAttackComponent::DisableSecondaryHitBox()
{
	if (_boxCollision2)
		_boxCollision2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

									 
void UAttackComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() == OtherActor)
		return;

	UDamageComponent* damageComp = OtherActor->GetComponentByClass<UDamageComponent>();
	if (damageComp)
		damageComp->TakeDamage(_myStats);
}


