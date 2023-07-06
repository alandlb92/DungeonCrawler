// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CharacterStats.h"
#include "Helpers/RPGCalculatorHelper.h"

CharacterStats::CharacterStats(UAttributesData* _attributes, DieEvent onDie)
{
	if (_attributes) {
		_maxLife = RPGCalculatorHelper::CalculateMaxLife(_attributes);
		_currentLife = _maxLife;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("_attributes is NULL"));


	_onDie = onDie;

	damageTextColor = FColor::Red;
	healTextColor = FColor::Green;
}

void CharacterStats::TakeDamage(UAttributesData* _atributesAttacking, UAttributesData* _atributesTaking)
{
	float damage = RPGCalculatorHelper::CalculateDamage(_atributesAttacking, _atributesTaking);

	_currentLife -= damage;

	if (_currentLife <= 0) {
		_onDie.ExecuteIfBound();
	}

	FMath::Clamp(_currentLife, 0, _maxLife);
	float percentage = _currentLife / _maxLife;
	_onChangeHp.Broadcast(percentage, damage, damageTextColor);
}

void CharacterStats::Heal(float amount)
{
	_currentLife += amount;
	if (_currentLife > _maxLife) {
		_currentLife = _maxLife;
	}

	float percentage = _currentLife / _maxLife;
	_onChangeHp.Broadcast(percentage, amount, healTextColor);
}

float CharacterStats::GetCurrentLife()
{
    return _currentLife;
}
