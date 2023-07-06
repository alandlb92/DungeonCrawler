// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributesData.h"

DECLARE_DELEGATE(DieEvent);
DECLARE_MULTICAST_DELEGATE_ThreeParams(NotifyHpChange, float, float, FColor)

/**
 *
 */
	class DUNGEONCRAWLER_API CharacterStats
{
public:
	CharacterStats(UAttributesData* _atributes, DieEvent onDie);
	void TakeDamage(UAttributesData* _atributesAttacking, UAttributesData* _atributesTaking);
	void Heal(float amount);
	NotifyHpChange _onChangeHp;
	float GetCurrentLife();
	FColor damageTextColor;
	FColor healTextColor;

private:
	DieEvent _onDie;
	float _currentLife;
	float _maxLife;
};
