// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributesData.h"

/**
 * 
 */


class DUNGEONCRAWLER_API RPGCalculatorHelper
{
public:
	static float CalculateMaxLife(UAttributesData* _attributes);
	static float CalculateDamage(UAttributesData* _attributesAttacking, UAttributesData* _attributesTaking);
	static float CalculateMovementSpeed(UAttributesData* _attributes);
	static float CalculateAttackSpeed(UAttributesData* _attributes);
};
