// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributesData.h"

DECLARE_MULTICAST_DELEGATE(CharacterStatsNotification);
DECLARE_MULTICAST_DELEGATE_OneParam(BoostTimerNotification, float);
DECLARE_MULTICAST_DELEGATE_ThreeParams(NotifyHpChange, float, float, FColor)

/**
 *
 */
	class DUNGEONCRAWLER_API CharacterStats
{
public:
	CharacterStats(UAttributesData* atributes);
	void UpdateTimers(float DeltaTime);
	void TakeDamage(CharacterStats* _statsAttacking, float multiplier);
	void Heal(float amount);

	void AddTempBoostSpeed(float amount, float time);
	void AddTempBoostAttack(float amount, float time);
	void AddTempBoostDefense(float amount, float time);

	void ClearTempBoostSpeed();
	void ClearTempBoostAttack();
	void ClearTempBoostDefense();

	NotifyHpChange _onChangeHp;
	CharacterStatsNotification _onDie;
	CharacterStatsNotification _onChangeSpeed;
	BoostTimerNotification _onNotifyTempSpeedBoostTime;
	BoostTimerNotification _onNotifyTempAttackBoostTime;
	BoostTimerNotification _onNotifyTempDefenseBoostTime;

	float GetCurrentLife();
	FColor damageTextColor;
	FColor healTextColor;	

private:	
	float _staticConstitution;
	float _staticAttack;
	float _staticDefense;
	float _staticSpeed;

	float _currentLife;
	float _maxLife;

	//Boosts
	float _tempSpeedBoost = 0;
	float _tempAttackBoost = 0;
	float _tempDefenseBoost = 0;

	//current time of boosts
	float _timeTempSpeedBoost = 0;
	float _timeTempAttackBoost = 0;
	float _timeTempDefenseBoost = 0;

public:
	float GetCurrentAttack() const;
	float GetCurrentDefense() const;
	float GetCurrentSpeed() const;
	float GetCurrentConst() const;

};
