// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/RPGCalculatorHelper.h"
//#include "Math/UnrealMathUtility.h"

float RPGCalculatorHelper::CalculateMaxLife(UAttributesData* _attributes)
{
	float result = 10;
	result *= _attributes->Constitution;
	return result;
}

float RPGCalculatorHelper::CalculateDamage(UAttributesData* _attributesAttacking, UAttributesData* _attributesTaking)
{
	//Add a random value to change a little the damage

	float fullDamage = 5;
	fullDamage *= _attributesAttacking->Attack;

	float defenseModifier = 2;
	defenseModifier *= _attributesTaking->Defense;

	return FMath::Clamp(fullDamage - defenseModifier, 1, INFINITY);
}
