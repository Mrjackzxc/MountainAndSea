// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/TsingletonBase.h"
#include "DelegateCombinations.h"
#include "System/StatMachine/ICharStatBase.h"
/**
 * 角色基础动画状态机
 */
#define ADD_STAT_TYPE 


DECLARE_MULTICAST_DELEGATE_TwoParams(RoleStatChangeDelegate, int32, int32);

class MOUNTAINANDSEA_API CRoleStatMachine
{
	friend class AMainCharacter;
protected:
	CRoleStatMachine(AMainCharacter * const charPtr);
	CRoleStatMachine();
	//CRoleStatMachine(const CRoleStatMachine & machine) {};
	~CRoleStatMachine();
protected:
	TSharedPtr<ICharStatBase> m_pCurrentStat;

	AMainCharacter * const m_pRolePtr;
public:
	RoleStatChangeDelegate m_nMachineStatDelegate;

public:
	bool ChangeStatWithValid(ECharBaseStat eSatType);

	void ChangeStat(ECharBaseStat eStatType);

	bool ValidStatChange(ECharBaseStat eSatType);

	ECharBaseStat GetStat() const;

	TSharedPtr<ICharStatBase> CreateStat(ECharBaseStat);

public://bind Delegate
	void BindRoleStatDelegate(UObject * Lisen);

};
