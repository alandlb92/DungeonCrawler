// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"
#include "Components/MeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	_mesh = GetOwner()->GetComponentByClass<UMeshComponent>();
	if (!_mesh)
		UE_LOG(LogTemp, Error, TEXT("Error on searching for the UMeshComponent"));

	UCapsuleComponent* capsuleComp = GetOwner()->GetComponentByClass<UCapsuleComponent>();
	if (capsuleComp) {
		capsuleComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		capsuleComp->OnBeginCursorOver.AddDynamic(this, &UInteractableComponent::BeginCursorOver);
		capsuleComp->OnEndCursorOver.AddDynamic(this, &UInteractableComponent::EndCursorOver);
	}

}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractableComponent::BeginCursorOver(UPrimitiveComponent* TouchedActor)
{
	if (_mesh)
		_mesh->SetRenderCustomDepth(true);
}

void UInteractableComponent::EndCursorOver(UPrimitiveComponent* TouchedActor)
{
	if (_mesh)
		_mesh->SetRenderCustomDepth(false);
}

