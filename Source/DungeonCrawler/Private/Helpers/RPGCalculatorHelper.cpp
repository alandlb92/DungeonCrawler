// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/RPGCalculatorHelper.h"
//#include "Math/UnrealMathUtility.h"

float RPGCalculatorHelper::CalculateMaxLife(CharacterStats* _stats)
{
	float result = 10;
	result *= _stats->GetCurrentConst();
	return result;
}

float RPGCalculatorHelper::CalculateDamage(CharacterStats* _attributesAttacking, CharacterStats* _attributesTaking)
{
	//Add a random value to change a little the damage

	float fullDamage = RollDice(8);
	fullDamage *= _attributesAttacking->GetCurrentAttack();

	float defenseModifier = RollDice(4);
	defenseModifier *= _attributesTaking->GetCurrentDefense();

	return FMath::Clamp(fullDamage - defenseModifier, 1, INFINITY);
}

float RPGCalculatorHelper::CalculateMovementSpeed(CharacterStats* _attributes)
{
	float speedBase = 50;
	return speedBase * _attributes->GetCurrentSpeed();
}

float RPGCalculatorHelper::CalculateAttackSpeed(CharacterStats* _attributes)
{
	return _attributes->GetCurrentSpeed() / 10;
}

int RPGCalculatorHelper::RollDice(int faces)
{
	return FMath::RandRange(1, faces);
}
