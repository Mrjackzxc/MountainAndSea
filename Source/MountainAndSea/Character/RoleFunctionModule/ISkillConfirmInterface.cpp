#include "ISkillConfirmInterface.h"
#include "System/TableManager/CTableManager.h"
#include "System/MountainAndSeaBaseDataDef.h"
#include "SKillComponent.h"



ISkillConfirmInterface::ISkillConfirmInterface(USKillComponent * AttachTo):ParentComponent(AttachTo)
{
	
}


ISkillConfirmInterface::~ISkillConfirmInterface()
{
}

CSkillGroupConfirm::CSkillGroupConfirm(USKillComponent * AttachTo):ISkillConfirmInterface(AttachTo)
{
	LoadConfig();
}

CSkillGroupConfirm::~CSkillGroupConfirm()
{

}

void CSkillGroupConfirm::LoadConfig()
{
// 	SkillKeyValue["q"] = Base_Element_Metal;
// 	SkillKeyValue["e"] = Base_Element_Wood;
// 	SkillKeyValue["r"] = Base_Element_Water;
// 	SkillKeyValue["z"] = Base_Element_Fire;
// 	SkillKeyValue["c"] = Base_Element_Earth;
	SkillKeyValue.Add(TEXT("Q"), Base_Element_Metal);
	SkillKeyValue.Add(TEXT("E"), Base_Element_Wood);
	SkillKeyValue.Add(TEXT("R"), Base_Element_Water);
	SkillKeyValue.Add(TEXT("Z"), Base_Element_Fire);
	SkillKeyValue.Add(TEXT("C"), Base_Element_Earth);
}

void CSkillGroupConfirm::OnSkillKeyBoardEnter(const FString & key)
{
	if (SkillKeyValue.Contains(key))
	{
		m_SelectSkillGroup.add(SkillKeyValue[key]);
	}
}

const FSkillDataBase * CSkillGroupConfirm::EnsureSkill()
{
	return CTableWrapper<FSkillDataBase>::GetItem(m_SelectSkillGroup.getKey()+GetSkillLevel());
}

void CSkillGroupConfirm::LunchSkill()
{
	const FSkillDataBase * skillData = EnsureSkill();
	ParentComponent->StartSkill(skillData);
}

CSkillSingleConfirm::CSkillSingleConfirm(USKillComponent * AttachTo):ISkillConfirmInterface(AttachTo),m_nSelectSkillId(0)
{
	LoadConfig();
}

CSkillSingleConfirm::~CSkillSingleConfirm()
{

}

void CSkillSingleConfirm::LoadConfig()
{
	//TODO:Load Skill Config
	SkillKeyValue.Add(TEXT("Q"), 111);
	SkillKeyValue.Add(TEXT("E"), 112);
	SkillKeyValue.Add(TEXT("R"), 113);
	SkillKeyValue.Add(TEXT("Z"), 114);
	SkillKeyValue.Add(TEXT("C"), 115);
}

void CSkillSingleConfirm::OnSkillKeyBoardEnter(const FString & key)
{
	if (SkillKeyValue.Contains(key))
	{
		m_nSelectSkillId = SkillKeyValue[key]*10;
	}
	else
	{
		m_nSelectSkillId = 0;
	}
	const FSkillDataBase * _skilData = EnsureSkill();
	ParentComponent->StartSkill(_skilData);
}

const FSkillDataBase * CSkillSingleConfirm::EnsureSkill()
{
	return CTableWrapper<FSkillDataBase>::GetItem(m_nSelectSkillId+GetSkillLevel());
}

void CSkillSingleConfirm::LunchSkill()
{
	
}
