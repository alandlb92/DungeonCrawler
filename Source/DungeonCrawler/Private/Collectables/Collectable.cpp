// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectables/Collectable.h"

// Sets default values
ACollectable::ACollectable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = _sceneComponent;

	_mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_mesh->SetupAttachment(_sceneComponent);

	_interactArea = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("Interactable Area"));
	_interactArea->SetupAttachment(_sceneComponent);
	_interactArea->SetCollisionObjectType(ECollisionChannel::ECC_OverlapAll_Deprecated);
	_interactArea->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	if (_interactArea) {
		_interactArea->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
	}

	_command = FindComponentByClass<UCommandCollectablesComponentBase>();
	if (!_command)
		UE_LOG(LogTemp, Error, TEXT("CommandCollectablesComponent not found on: %s"), *GetName());

}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		if (_command) {
			_command->Execute();
		}

		Destroy();
	}
}