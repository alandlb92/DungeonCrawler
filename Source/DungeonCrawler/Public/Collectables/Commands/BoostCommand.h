// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CommandCollectablesComponentBase.h"
#include "BoostCommand.generated.h"

UENUM(BlueprintType)
enum BoostType : uint8
{
	BSPEED UMETA(DisplayName = "Speed Boost"),
	BATTACK UMETA(DisplayName = "Atack boost"),
	BDEFENSE UMETA(DisplayName = "Defense Boost")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONCRAWLER_API UBoostCommand : public UCommandCollectablesComponentBase
{
	GENERATED_BODY()
public:
	void Execute() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<BoostType> _boostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _boostPower = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _boostTime = 60;
};
