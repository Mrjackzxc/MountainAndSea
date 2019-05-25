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
	SkillKeyValue.Add("Q", Base_Element_Metal);
	SkillKeyValue.Add("E", Base_Element_Wood);
	SkillKeyValue.Add("R", Base_Element_Water);
	SkillKeyValue.Add("Z", Base_Element_Fire);
	SkillKeyValue.Add("C", Base_Element_Earth);
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
	SkillKeyValue.Add("Q", 10010);
	SkillKeyValue.Add("E", 10020);
	SkillKeyValue.Add("R", 10030);
	SkillKeyValue.Add("Z", 10040);
	SkillKeyValue.Add("C", 10050);
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
