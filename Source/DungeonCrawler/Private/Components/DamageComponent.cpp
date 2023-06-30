// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageComponent.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDamageComponent::Configure(UAttributesData* myAttributes, CharacterStats* myStats)
{
	_myAttributes = myAttributes;
	_myStats = myStats;
}

// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...	
}

// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDamageComponent::TakeDamage(UAttributesData* otherAttributes)
{
	_myStats->TakeDamage(otherAttributes, _myAttributes);
}
