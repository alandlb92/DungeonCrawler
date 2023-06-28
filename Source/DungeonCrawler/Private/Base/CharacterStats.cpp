// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CharacterStats.h"
#include "Helpers/RPGCalculatorHelper.h"

CharacterStats::CharacterStats(UAttributesData* _attributes, DieEvent onDie)
{
	if (_attributes)
		_currentLife = RPGCalculatorHelper::CalculateMaxLife(_attributes);
	else
		UE_LOG(LogTemp, Error, TEXT("_attributes is NULL"));

	_onDie = onDie;
}

void CharacterStats::TakeDamage(UAttributesData* _atributesAttacking, UAttributesData* _atributesTaking)
{

	float damage = RPGCalculatorHelper::CalculateDamage(_atributesAttacking, _atributesTaking);
	UE_LOG(LogTemp, Warning, TEXT("Attack dammage: %f"), damage);

	_currentLife -= damage;
	UE_LOG(LogTemp, Warning, TEXT("CurrentLife: %f"), _currentLife);
	if (_currentLife <= 0)
		_onDie.ExecuteIfBound();
}
