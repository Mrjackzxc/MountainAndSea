// Fill out your copyright notice in the Description page of Project Settings.

#include "ICharStatBase.h"
#include "Character/MainCharacter.h"

ICharStatBase::ICharStatBase(ECharBaseStat eStatType):m_nCharBaseStat(eStatType)
{
	
}

ICharStatBase::~ICharStatBase()
{
} 

bool ICharStatBase::ValidChangeStat(ECharBaseStat eStat)
{
	return m_nStatValid & eStat;
}

void ICharStatBase::SetStatValid(TArray<ECharBaseStat> eStat)
{
	for (size_t i=0;i<eStat.Num();i++)
	{
		m_nStatValid |= eStat[i];
	}
}

//void ICharStatBase::SetStatValid(int32 nParamCoubnt,ECharBaseStat eStatType, ...)
//{
//	ECharBaseStat * _pStatList = &eStatType;
//	for (size_t i=0;i<nParamCoubnt;i++)
//	{
//		m_nStatValid |= *_pStatList;
//		_pStatList++;
//	}
//}


CharStatIdle::CharStatIdle():ICharStatBase(IdleStat)
{
	SetStatValid({CombatStat, SKillStat, UsepropStat,JumpStat,IdleStat });
}

CharStatIdle::~CharStatIdle()
{

}


void CharStatIdle::OnLeaveStat(AMainCharacter * m_pRolePtr)
{
	if (m_pRolePtr==nullptr)
	{
		return;
	}
}

void CharStatIdle::OnGetIntoStat(AMainCharacter * m_pRolePtr)
{
	
}

void CharStatIdle::OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat)
{

}

CharStatJump::CharStatJump():ICharStatBase(JumpStat)
{
	SetStatValid({IdleStat,ControlStat});
}

CharStatJump::~CharStatJump()
{

}

void CharStatJump::OnLeaveStat(AMainCharacter * m_pRolePtr)
{

}

void CharStatJump::OnGetIntoStat(AMainCharacter * m_pRolePtr)
{
	m_pRolePtr->Jump();
}

void CharStatJump::OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat)
{

}

CharStatSkill::CharStatSkill() :ICharStatBase(SKillStat)
{
	SetStatValid({ SKillStat,IdleStat, ControlStat});
}

CharStatSkill::~CharStatSkill()
{

}

void CharStatSkill::OnLeaveStat(AMainCharacter * m_pRolePtr)
{
	m_pRolePtr->SetRoleCanMove(true);
	m_pRolePtr->SetRoleCanMove(true);
}

void CharStatSkill::OnGetIntoStat(AMainCharacter * m_pRolePtr)
{
	if (!m_pRolePtr->GetRoleSkillComponent()->GetSkillIsAllowMove())
	{
		m_pRolePtr->SetRoleCanMove(false) ;
		m_pRolePtr->SetRoleCanMove(false);
	}
	else {
		m_pRolePtr->SetRoleCanMove(true);
		m_pRolePtr->SetRoleCanMove(true);
	}
}

void CharStatSkill::OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat)
{

}

CharStatControl::CharStatControl():ICharStatBase(ControlStat)
{
	SetStatValid({IdleStat, ControlStat});
}

CharStatControl::~CharStatControl()
{
	
}

void CharStatControl::OnLeaveStat(AMainCharacter * m_pRolePtr)
{

}

void CharStatControl::OnGetIntoStat(AMainCharacter * m_pRolePtr)
{

}

void CharStatControl::OnLeaveStatFailed(AMainCharacter * m_pRolePtr, ECharBaseStat newStat)
{

}
