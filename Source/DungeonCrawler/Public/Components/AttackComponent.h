// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Base/CharacterStats.h"
#include "Data/AttributesData.h"
#include "AttackComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONCRAWLER_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAttackComponent();
	void Configure(UAttributesData* myAttributes, CharacterStats* myStats);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void EnableHitBox();
	void DisableHitBox();

	void EnableSecondaryHitBox();
	void DisableSecondaryHitBox();

private:
	
	UAttributesData* _myAttributes;
	CharacterStats* _myStats;

	class UBoxComponent* _boxCollision1;
	class UBoxComponent* _boxCollision2;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
