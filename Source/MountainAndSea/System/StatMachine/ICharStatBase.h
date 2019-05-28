// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharBaseInfoDef.h"


/**
 * Role Stat 
Valid and Get In To Stat
 */
class AMainCharacter;

class MOUNTAINANDSEA_API ICharStatBase
{
	friend class CRoleStatMachine;
protected:
	ICharStatBase(ECharBaseStat);
	virtual ~ICharStatBase();

protected:
	ECharBaseStat m_nCharBaseStat= ECharBaseStat::InValidStat;

	int32 m_nStatValid= 0;
protected:
	ECharBaseStat GetCurrentStat()const { return m_nCharBaseStat; }

	virtual bool ValidChangeStat(ECharBaseStat);

	/*virtual void SetStatValid(int32 nParamCoubnt,ECharBaseStat eStat ,...);*/
	void SetStatValid(TArray<ECharBaseStat> eStat) ;

	virtual void OnLeaveStat(AMainCharacter * m_pRolePtr)=0 ;
	 
	virtual void OnGetIntoStat(AMainCharacter * m_pRolePtr)=0 ;

	virtual void OnLeaveStatFailed(AMainCharacter * m_pRolePtr,ECharBaseStat newStat) = 0;

};

class CharStatIdle:public ICharStatBase
{
public:
	CharStatIdle();
	~CharStatIdle();

protected:
	void OnLeaveStat(AMainCharacter * m_pRolePtr) override;

	void OnGetIntoStat(AMainCharacter * m_pRolePtr) override;

	void OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat) override;
};

class CharStatJump :public ICharStatBase
{
public:
	CharStatJump();
	~CharStatJump();

protected:
	void OnLeaveStat(AMainCharacter * m_pRolePtr) override;

	void OnGetIntoStat(AMainCharacter * m_pRolePtr) override;

	void OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat) override;
};

class CharStatSkill :public ICharStatBase
{
public:
	CharStatSkill();

	~CharStatSkill();
protected:
	void OnLeaveStat(AMainCharacter * m_pRolePtr) override;

	void OnGetIntoStat(AMainCharacter * m_pRolePtr) override;

	void OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat) override;
};

class CharStatControl :public ICharStatBase
{
public:
	CharStatControl();

	~CharStatControl();
protected:
	void OnLeaveStat(AMainCharacter * m_pRolePtr) override;

	void OnGetIntoStat(AMainCharacter * m_pRolePtr) override;

	void OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat) override;
};
