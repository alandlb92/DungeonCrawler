// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CharacterStats.h"
#include "Helpers/RPGCalculatorHelper.h"

CharacterStats::CharacterStats(UAttributesData* attributes)
{
	if (attributes) {
		_staticAttack = attributes->Attack;
		_staticDefense = attributes->Defense;
		_staticSpeed = attributes->Speed;
		_staticConstitution = attributes->Constitution;
		_maxLife = RPGCalculatorHelper::CalculateMaxLife(this);
		_currentLife = _maxLife;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("_attributes is NULL"));

	damageTextColor = FColor::Red;
	healTextColor = FColor::Green;	
}

void CharacterStats::UpdateTimers(float DeltaTime)
{
	if (_timeTempSpeedBoost != 0)
	{
		_timeTempSpeedBoost -= DeltaTime;
		if (_timeTempSpeedBoost <= 0)
			ClearTempBoostSpeed();
		else
			_onNotifyTempSpeedBoostTime.Broadcast(_timeTempSpeedBoost);
	}

	if (_timeTempAttackBoost != 0)
	{
		_timeTempAttackBoost -= DeltaTime;
		if (_timeTempAttackBoost <= 0)
			ClearTempBoostAttack();
		else
			_onNotifyTempAttackBoostTime.Broadcast(_timeTempAttackBoost);
	}

	if (_timeTempDefenseBoost != 0)
	{
		_timeTempDefenseBoost -= DeltaTime;
		if (_timeTempDefenseBoost <= 0)
			ClearTempBoostDefense();
		else
			_onNotifyTempDefenseBoostTime.Broadcast(_timeTempDefenseBoost);
	}

}

void CharacterStats::TakeDamage(CharacterStats* _statsAttacking, float multiplier)
{
	float damage = RPGCalculatorHelper::CalculateDamage(_statsAttacking, this);
	damage *= multiplier;
	_currentLife -= damage;

	if (_currentLife <= 0) {
		_onDie.Broadcast();
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


void CharacterStats::AddTempBoostSpeed(float amount, float timeSeconds)
{
	_tempSpeedBoost = amount;
	_timeTempSpeedBoost = timeSeconds;
	_onChangeSpeed.Broadcast();
}

void CharacterStats::ClearTempBoostSpeed()
{
	_tempSpeedBoost = 0;
	_timeTempSpeedBoost = 0;
	_onChangeSpeed.Broadcast();
	_onNotifyTempSpeedBoostTime.Broadcast(0);
}

void CharacterStats::AddTempBoostAttack(float amount, float timeSeconds)
{
	_tempAttackBoost= amount;
	_timeTempAttackBoost = timeSeconds;
}

void CharacterStats::ClearTempBoostAttack()
{
	_tempAttackBoost = 0;
	_timeTempAttackBoost = 0;
	_onNotifyTempAttackBoostTime.Broadcast(0);
}

void CharacterStats::AddTempBoostDefense(float amount, float timeSeconds)
{
	_tempDefenseBoost = amount;
	_timeTempDefenseBoost = timeSeconds;
}

void CharacterStats::ClearTempBoostDefense()
{
	_tempDefenseBoost = 0;
	_timeTempDefenseBoost = 0;
	_onNotifyTempDefenseBoostTime.Broadcast(_timeTempDefenseBoost);
}

float CharacterStats::GetCurrentLife()
{
    return _currentLife;
}

float CharacterStats::GetCurrentAttack() const
{
	return _staticAttack + _tempAttackBoost;
}

float CharacterStats::GetCurrentDefense() const
{
	return _staticDefense + _tempDefenseBoost;
}

float CharacterStats::GetCurrentSpeed() const
{
	return _staticSpeed + _tempSpeedBoost;
}

float CharacterStats::GetCurrentConst() const
{
	return _staticConstitution;
}
