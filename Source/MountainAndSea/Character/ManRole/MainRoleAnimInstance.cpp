// Fill out your copyright notice in the Description page of Project Settings.

#include "MainRoleAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/Engine.h"


void UMainRoleAnimInstance::NativeInitializeAnimation()
{
	APawn * _pOwner = TryGetPawnOwner();
	m_pMainRole = Cast<AMainCharacter>(_pOwner);
}

void UMainRoleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (m_pMainRole==nullptr)
	{
		return;
	}
	m_eRoleStat = m_pMainRole->GetRoleStat();
	m_pMainRole->GetMovementComponent()->Velocity.ToDirectionAndLength(m_vMoveDir, m_nRoleMoveSpeed);
	if (m_nRoleMoveSpeed!=0)
	{
		m_nRoleMoveSpeed /= m_pMainRole->GetMovementComponent()->GetMaxSpeed();
		FVector _tempVector = m_pMainRole->GetActorForwardVector();
		FVector _actorRight = m_pMainRole->GetActorRightVector();
		int32 _sign = (_actorRight^m_vMoveDir).Z > 0 ? -1 : 1;
		m_nRoleMoveDir = FMath::Acos(_tempVector*_sign | m_vMoveDir)/(PI)*180;
		m_nRoleMoveDir *= (_tempVector^m_vMoveDir).Z > 0 ? -1 : 1;
		m_nRoleMoveSpeed *= _sign;
	}
	else
	{
		m_nRoleMoveDir = 0;
	}
	m_bInAir = m_pMainRole->GetMovementComponent()->IsFalling();
}

FRotator UMainRoleAnimInstance::GetRoleControllerRotation()
{
	if (m_pMainRole!=nullptr)
	{
		return m_pMainRole->GetRoleRotator();
	}
	return FRotator::ZeroRotator;
}

FRotator UMainRoleAnimInstance::GetRoleControllerRotationDelta()
{
	if (m_pMainRole != nullptr)
	{
		return m_pMainRole->GetRotatorDelta();
	}
	return FRotator::ZeroRotator;
}


