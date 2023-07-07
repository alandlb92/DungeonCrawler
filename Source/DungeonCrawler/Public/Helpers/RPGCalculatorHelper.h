// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributesData.h"
#include "Base/CharacterStats.h"

/**
 * 
 */


class DUNGEONCRAWLER_API RPGCalculatorHelper
{
public:
	static float CalculateMaxLife(CharacterStats* _constAtrib);
	static float CalculateDamage(CharacterStats* _attributesAttacking, CharacterStats* _attributesTaking);
	static float CalculateMovementSpeed(CharacterStats* _attributes);
	static float CalculateAttackSpeed(CharacterStats* _attributes);
	static int RollDice(int faces);
};
