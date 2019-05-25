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
	AMainCharacter * _pOwner = Cast<AMainCharacter>(GetOwner());
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

void USKillComponent::OnChangePhase(const FSkillDataBase * skillData)
{

}

void USKillComponent::StartSkill(const FSkillDataBase * skillData)
{
	if (skillData == nullptr||m_pMainCharacter==nullptr)
	{
		//TODO:Show SystemNotify
		return;
	}
	if (m_pMainCharacter->ChangeRoleStat(SKillStat))
	{
		_preparePlaySkill(skillData);
	}
} 

void USKillComponent::_preparePlaySkill(const FSkillDataBase * skillData)
{
	for (size_t i = 0; i < skillData->PhaseStep.Num(); i++)
	{
		const FSkillPhaseStruct & _skillPhase = skillData->PhaseStep[i];
		if (_skillPhase.SkillPhase == 0)
		{
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
		}
	}
}

void USKillComponent::_playingSkill(const FSkillDataBase * skillData)
{
	for (size_t i = 0; i < skillData->PhaseStep.Num(); i++)
	{
		const FSkillPhaseStruct & _skillPhase = skillData->PhaseStep[i];
		if (_skillPhase.SkillPhase == 1)
		{
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
		}
	}
	_endingSkill(skillData);
}

void USKillComponent::_endingSkill(const FSkillDataBase * skillData)
{
	for (size_t i = 0; i < skillData->PhaseStep.Num(); i++)
	{
		const FSkillPhaseStruct & _skillPhase = skillData->PhaseStep[i];
		if (_skillPhase.SkillPhase == 2)
		{
			m_pMainCharacter->StopAnimMontage();
			m_pMainCharacter->PlayAnimMontage(_skillPhase.SkillAnimMontage);
		}
	}
}

void USKillComponent::ResponseSkillkeyboard(FString key)
{
	m_pSkillConfirm->OnSkillKeyBoardEnter(key);
}

void USKillComponent::LunchSkill()
{
	m_pSkillConfirm->LunchSkill();
}

