// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_OnSkillMontageEnd.h"
#include "../MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotify_OnSkillMontageEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AMainCharacter * _pCharacter = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (_pCharacter!=nullptr)
	{
		_pCharacter->GetRoleSkillComponent()->OnChangePhase();
	}
}
