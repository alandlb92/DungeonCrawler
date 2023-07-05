#include "Components/CommandCollectablesComponentBase.h"
// Fill out your copyright notice in the Description page of Project Se#include "Components/CommandCollectablesComponentBase.h"

// Sets default values for this component's properties
UCommandCollectablesComponentBase::UCommandCollectablesComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCommandCollectablesComponentBase::BeginPlay()
{
	Super::BeginPlay();
	_player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (!_player)
	{
		UE_LOG(LogTemp, Error, TEXT("APlayerCharacter not found on UCommandCollectablesComponentBase::BeginPlay"));
	}

	// ...
	
}


// Called every frame
void UCommandCollectablesComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCommandCollectablesComponentBase::Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("UCommandCollectablesComponentBase::Execute"));
}

