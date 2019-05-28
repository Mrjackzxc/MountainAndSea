// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillComponent.h"
#include "ISkillConfirmInterface.h"
#include "../MainCharacter.h"

// Sets default values for this component's properties
USKillComponent::USKillComponent():m_nCurrentSkillId(0),m_bIsGroup(true)
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
	return true;
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
		_interruptSkill();
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
	m_pCurrentSkillData = MakeShared<FSkillDataBase>(*skillData);
	if (m_pCurrentSkillData.IsValid()&&m_pMainCharacter->ChangeRoleStat(SKillStat) )
	{
		_preparePlaySkill();
	}
} 

void USKillComponent::_preparePlaySkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		for (size_t i = 0; i < m_pCurrentSkillData->PhaseStep.Num(); i++)
		{
			const FSkillPhaseStruct & _skillPhase = m_pCurrentSkillData->PhaseStep[i];
			if (_skillPhase.SkillPhase == Phase_Prepare)
			{
				m_nSkillPhase = (ESkillPhaseEnum)_skillPhase.SkillPhase;
				m_pMainCharacter->StopAnimMontage();
				m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
				return;
			}
		}
		_playingSkill();
	}
	
}

void USKillComponent::_playingSkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		for (size_t i = 0; i < m_pCurrentSkillData->PhaseStep.Num(); i++)
		{
			const FSkillPhaseStruct & _skillPhase = m_pCurrentSkillData->PhaseStep[i];
			if (_skillPhase.SkillPhase == Phase_Playing)
			{
				m_nSkillPhase = (ESkillPhaseEnum)_skillPhase.SkillPhase;
				m_pMainCharacter->StopAnimMontage();
				m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
				return;
			}
		}
	}
}

void USKillComponent::_endingSkill()
{
	if (m_pCurrentSkillData.IsValid())
	{
		for (size_t i = 0; i < m_pCurrentSkillData->PhaseStep.Num(); i++)
		{
			const FSkillPhaseStruct & _skillPhase = m_pCurrentSkillData->PhaseStep[i];
			if (_skillPhase.SkillPhase == Phase_Ending)
			{
				m_nSkillPhase = (ESkillPhaseEnum)_skillPhase.SkillPhase;
				m_pMainCharacter->StopAnimMontage();
				m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
				return;
			}
		}
	}
	_interruptSkill();
}

void USKillComponent::_interruptSkill()
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

