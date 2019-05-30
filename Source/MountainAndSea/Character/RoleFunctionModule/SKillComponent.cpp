// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillComponent.h"
#include "ISkillConfirmInterface.h"
#include "../MainCharacter.h"
#include "System/Skill/SkillInstance.h"
#include "Engine/World.h"
#include "System/TableManager/CTableManager.h"

// Sets default values for this component's properties
USKillComponent::USKillComponent():m_nCurrentSkillId(0),m_bIsGroup(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ChangeSkillOperationType(LoadCharOperationType());
	m_pMainCharacter = Cast<AMainCharacter>(GetOwner());
	// ...
}

// Called when the game starts
void USKillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool USKillComponent::LoadCharOperationType()
{
	//TODO:
	return false;
}

void USKillComponent::SaveCharOperationType()
{
	//TODO:
}

void USKillComponent::ChangeSkillOperationType(bool newType)
{
	m_bIsGroup = newType;
	if (m_bIsGroup)
	{
		m_pSkillConfirm = MakeShared<CSkillGroupConfirm>(this);
	}
	else
	{
		m_pSkillConfirm = MakeShared<CSkillSingleConfirm>(this);
	}
}

// Called every frame
void USKillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USKillComponent::OnChangePhase()
{
	switch (m_nSkillPhase)
	{
	case Phase_Prepare:
		_playingSkill();
		return;
	case Phase_Playing:
		_endingSkill();
		return;
	case Phase_Ending:
		InterruptSkill();
		return;
	default:
		m_pMainCharacter->OnSkillEnd();
		return;
	}
}

void USKillComponent::StartSkill(const FSkillDataBase * skillData)
{
	if (skillData == nullptr||m_pMainCharacter==nullptr)
	{
		//TODO:Show SystemNotify
		return;
	}
	if (ValidateSkill(skillData)&&m_pMainCharacter->ChangeRoleStat(SKillStat) )
	{
		_preparePlaySkill();
	}
} 

bool USKillComponent::ValidateSkill(const FSkillDataBase * skillData)
{
	if (skillData == nullptr || m_pMainCharacter == nullptr)
	{
		//TODO:Show SystemNotify
		return false;
	}
	if (m_pCurrentSkillData.IsValid()&&!m_pCurrentSkillData->BeCancel)
	{
		return false;
	}
	m_pCurrentSkillData = MakeShared<FSkillDataBase>(*skillData);
	if (!m_pCurrentSkillData.IsValid())
	{
		return false;
	}
	return true;
}

void USKillComponent::_preparePlaySkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		if (m_pCurrentSkillData->PhaseStep.Contains(Phase_Prepare))
		{
			m_nSkillPhase = Phase_Prepare;
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(m_pCurrentSkillData->PhaseStep[Phase_Prepare].SkillAnimMontage);
			return;
		}
		_playingSkill();
	}
	
}

void USKillComponent::_playingSkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		if (m_pCurrentSkillData->PhaseStep.Contains(Phase_Playing))
		{
			m_nSkillPhase = Phase_Playing;
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(m_pCurrentSkillData->PhaseStep[Phase_Playing].SkillAnimMontage);
			return;
		}
	}
}

void USKillComponent::_endingSkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		if (m_pCurrentSkillData->PhaseStep.Contains(Phase_Ending))
		{
			m_nSkillPhase = Phase_Ending;
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(m_pCurrentSkillData->PhaseStep[Phase_Ending].SkillAnimMontage);
			return;
		}
	}
	InterruptSkill();
}

void USKillComponent::InterruptSkill()
{
	if (m_pMainCharacter!=nullptr)
	{
		m_pMainCharacter->StopAnimMontage();
		m_pMainCharacter->OnSkillEnd();
	}
	m_nSkillPhase = Phase_Max;
	m_pCurrentSkillData.Reset();
}

void USKillComponent::ResponseSkillkeyboard(FString key)
{
	m_pSkillConfirm->OnSkillKeyBoardEnter(key);
}

void USKillComponent::LunchSkill()
{
	m_pSkillConfirm->LunchSkill();
}

bool USKillComponent::GetSkillIsAllowMove() const
{
	if (m_pCurrentSkillData.IsValid())
	{
		return m_pCurrentSkillData->CanMove;
	}
	return true;
}

void USKillComponent::SpawnSkill()
{
	const FSkillInstanceData * _skillData = CTableWrapper<FSkillInstanceData>::GetItem(m_pCurrentSkillData->SkillInstanceId);
	if (_skillData == nullptr)
	{
		return;
	}
	//GetWorld()->SpawnActor<ASkillInstance>(_skillData,);
}
