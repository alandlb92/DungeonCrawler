// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttributesData.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONCRAWLER_API UAttributesData : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Constitution;
};
