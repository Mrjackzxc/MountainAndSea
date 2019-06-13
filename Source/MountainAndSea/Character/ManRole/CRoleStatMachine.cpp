// Fill out your copyright notice in the Description page of Project Settings.

#include "CRoleStatMachine.h"
#include "LogMacros.h"

CRoleStatMachine::CRoleStatMachine(AMainCharacter * const charPtr):m_pCurrentStat(MakeShared<CharStatIdle>()),m_pRolePtr(charPtr)
{
	
}

CRoleStatMachine::CRoleStatMachine() : m_pCurrentStat(MakeShared<CharStatIdle>()), m_pRolePtr(nullptr)
{

}

CRoleStatMachine::~CRoleStatMachine()
{
}

bool CRoleStatMachine::ChangeStatWithValid(ECharBaseStat eStatType)
{
	if (m_pCurrentStat.IsValid())
	{
		if (m_pCurrentStat->ValidChangeStat(eStatType))
		{
			ChangeStat(eStatType);
			return true;
		}
		m_pCurrentStat->OnLeaveStatFailed(m_pRolePtr, eStatType);
	}
	return false;
}

void CRoleStatMachine::ChangeStat(ECharBaseStat eStatType)
{
	m_pCurrentStat->OnLeaveStat(m_pRolePtr);
	m_pCurrentStat = CreateStat(eStatType);
	m_pCurrentStat->OnGetIntoStat(m_pRolePtr);
	return ;
}

bool CRoleStatMachine::ValidStatChange(ECharBaseStat eStatType)
{
	if (m_pCurrentStat.IsValid())
	{	
		return m_pCurrentStat->ValidChangeStat(eStatType);
	}
	UE_LOG(LogTemp, Log, TEXT("Current Stat Is Invalid"));
	return false;
}

ECharBaseStat CRoleStatMachine::GetStat() const
{
	if (m_pCurrentStat.IsValid())
	{
		return m_pCurrentStat->GetCurrentStat();
	}
	return ECharBaseStat::InValidStat;
}

TSharedPtr<ICharStatBase> CRoleStatMachine::CreateStat(ECharBaseStat eStat)
{
	switch (eStat)
	{
	case InValidStat:
		break;
	case IdleStat:
		return  MakeShared<CharStatIdle>();
	case JumpStat:
		return  MakeShared<CharStatJump>();
	case CombatStat:
		break;
	case SKillStat:
		return  MakeShared<CharStatSkill>();
	case UsepropStat:
		break;
	case ControlStat:
		return  MakeShared<CharStatControl>();
	case StatMax:
		break;
	}
	return nullptr;
}
