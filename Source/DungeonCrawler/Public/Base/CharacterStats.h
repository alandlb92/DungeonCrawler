// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AttributesData.h"

DECLARE_DELEGATE(DieEvent);
DECLARE_DELEGATE_OneParam(NotifyPrpertieChange, float)

/**
 * 
 */
class DUNGEONCRAWLER_API CharacterStats
{
public:
	CharacterStats(UAttributesData* _atributes, DieEvent onDie);
	void TakeDamage(UAttributesData* _atributesAttacking, UAttributesData* _atributesTaking);
	NotifyPrpertieChange _onChangeCurrentLife;

private:
	DieEvent _onDie;
	float _currentLife;
	float _maxLife;
};
