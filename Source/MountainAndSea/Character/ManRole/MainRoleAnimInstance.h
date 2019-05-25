// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../CharBaseInfoDef.h"
#include "../MainCharacter.h"
#include "MainRoleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MOUNTAINANDSEA_API UMainRoleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	ECharBaseStat m_eRoleStat;

	const AMainCharacter *m_pMainRole;

protected:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	FVector m_vMoveDir;
	//moveForwardSpeed
	float m_nRoleMoveSpeed;
	//moveRightSpeed
	float m_nRoleMoveDir;

	bool m_bInAir;
public:
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = RoleBase,meta=(DisplayName = "Role MoveSpeed", BlueprintThreadSafe))
		float GetRoleMoveSpeed()const { return m_nRoleMoveSpeed; }

	UFUNCTION(BlueprintCallable,  BlueprintPure, Category = RoleBase, meta=(DisplayName = "Role MoveDirection", BlueprintThreadSafe))
		float GetRoleMoveDir()const { return m_nRoleMoveDir; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RoleBase, meta = (DisplayName = "Role IsAir", BlueprintThreadSafe))
		bool GetRoleIsInAir()const { return m_bInAir; }
public:
	UFUNCTION(BlueprintCallable, Category = RoleBase)
		void SetRoleStats(ECharBaseStat eStat) { m_eRoleStat = eStat; };

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = RoleBase, meta = (DisplayName = "Role Stat", BlueprintThreadSafe))
		ECharBaseStat GetRoleStats() { return m_eRoleStat; };

	UFUNCTION(BlueprintCallable, BlueprintPure,Category = RoleBase, meta = (DisplayName = "Controller Rotation", BlueprintThreadSafe))
		FRotator GetRoleControllerRotation();

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = RoleBase, meta = (DisplayName = "Controller Rotation Delta", BlueprintThreadSafe))
		FRotator GetRoleControllerRotationDelta();

public:
// 	UFUNCTION(BlueprintCallable, Category = AnimationFunction)
// 		void PlaySkillMontage();
};
