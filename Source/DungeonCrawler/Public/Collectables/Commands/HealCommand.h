// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CommandCollectablesComponentBase.h"
#include "HealCommand.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONCRAWLER_API UHealCommand : public UCommandCollectablesComponentBase
{
	GENERATED_BODY()
public:
	void Execute() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _healPower = 10;
};
