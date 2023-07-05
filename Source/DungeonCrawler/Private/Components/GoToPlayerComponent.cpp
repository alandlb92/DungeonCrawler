// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GoToPlayerComponent.h"

// Sets default values for this component's properties
UGoToPlayerComponent::UGoToPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	_gotoArea = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("Active Goto Area"));
	_gotoArea->SetupAttachment(GetAttachmentRoot());
	_gotoArea->SetCollisionObjectType(ECollisionChannel::ECC_OverlapAll_Deprecated);
	_gotoArea->SetCanEverAffectNavigation(false);
	_gotoArea->SetSphereRadius(200);
}


// Called when the game starts
void UGoToPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (_gotoArea) {
		_gotoArea->OnComponentBeginOverlap.AddDynamic(this, &UGoToPlayerComponent::OnOverlapBegin);
	}
	// ...
	
}


// Called every frame
void UGoToPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_player)
	{
		FVector newPos = FMath::Lerp
		(GetOwner()->GetActorLocation(), _player->GetActorLocation(), _velocityAmount);
		GetOwner()->SetActorLocation(newPos);
	}
}

void UGoToPlayerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FTimerHandle UnusedHandle;
	GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, [this, OtherActor]()
	{
		_player = Cast<APlayerCharacter>(OtherActor);
	}, _delay, false);
}

