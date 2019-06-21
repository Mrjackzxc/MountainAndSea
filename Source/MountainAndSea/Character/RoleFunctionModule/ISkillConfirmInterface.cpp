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

const FSkillDataBase * ISkillConfirmInterface::EnsureSkill(int32 nSkillID)
{
	return CTableWrapper<FSkillDataBase>::GetItem(nSkillID + GetSkillLevel());
}

void ISkillConfirmInterface::LunchSkill()
{	
	ParentComponent->RPC_Server_LunchSkill(GetSkillID());
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
	SkillKeyValue.Add('Q', Base_Element_Metal);
	SkillKeyValue.Add('E', Base_Element_Wood);
	SkillKeyValue.Add('R', Base_Element_Water);
	SkillKeyValue.Add('Z', Base_Element_Fire);
	SkillKeyValue.Add('X', Base_Element_Earth);
}

void CSkillGroupConfirm::OnSkillKeyBoardEnter(const int8 & key)
{
	if (SkillKeyValue.Contains(key))
	{
		m_SelectSkillGroup.add(SkillKeyValue[key]);
	}
}

const int32 CSkillGroupConfirm::GetSkillID() const 
{
	return m_SelectSkillGroup.getKey();
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
	SkillKeyValue.Add('Q', 111);
	SkillKeyValue.Add('E', 112);
	SkillKeyValue.Add('R', 113);
	SkillKeyValue.Add('Z', 114);
	SkillKeyValue.Add('X', 115);
}

void CSkillSingleConfirm::OnSkillKeyBoardEnter(const int8 & key)
{
	if (SkillKeyValue.Contains(key))
	{
		m_nSelectSkillId = SkillKeyValue[key]*10;
	}
	else
	{
		m_nSelectSkillId = 0;
	}
	LunchSkill();
}

const int32 CSkillSingleConfirm::GetSkillID() const
{
	return m_nSelectSkillId;
}

