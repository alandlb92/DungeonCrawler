// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CommandCollectablesComponentBase.h"
#include "Collectable.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();
	UPROPERTY(EditAnywhere)
	USceneComponent* _sceneComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* _interactArea;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY()
	UCommandCollectablesComponentBase* _command;

};
