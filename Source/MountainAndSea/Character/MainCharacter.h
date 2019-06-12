// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharBaseInfoDef.h"
#include "ManRole/CRoleStatMachine.h"
#include "RoleFunctionModule/SKillComponent.h"
#include "MainCharacter.generated.h"


UCLASS()
class MOUNTAINANDSEA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USKillComponent * CharacterSkillComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//状态机数据管理
protected:
	CRoleStatMachine m_fStatMachine;

	bool m_bCanMove;

	bool m_bCanJump;
	
public:
	UFUNCTION(NetMulticast, Reliable)
		void RPC_Muitcast_ChangeRoleState(ECharBaseStat eStat);
	void RPC_Muitcast_ChangeRoleState_Implementation(ECharBaseStat eStat) 
	{ 
		if (ValidStatChange(eStat))
		{
			ChangeRoleStat((ECharBaseStat)eStat); 
		}
	}

	//get role Stat
	ECharBaseStat GetRoleStat() const;

	void OnRoleStatChange(ECharBaseStat eStat);

	bool ValidStatChange(ECharBaseStat eStat);

	void ChangeRoleStat(ECharBaseStat eStat);

	bool ChangeRoleStatWithValid(ECharBaseStat eStat);

	void SetRoleCanMove(bool canMove);

	void SetRoleCanJump(bool canJump);

	//方向，速度等基本数据
protected:
	FRotator m_fControllerRotator;

	FRotator m_fRoleRotator;
protected:
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
		float m_fYawLimit;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float m_fPitchHightLimit;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float m_fPitchLowLimit;

public:	
	FRotator GetRoleControllerRotator() const { return m_fControllerRotator; };

	FRotator GetRoleRotator() const { return m_fRoleRotator; };
	
	FRotator GetRotatorDelta() const { return m_fRoleRotator - m_fControllerRotator; };

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Role Base Info")
		FBaseElements m_nCharAttrBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role Base Data")
		FCharacterBaseInfo m_fHeroBaseInfo;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

public:
	//数据读取管理
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = RoleAttr)
		const FBaseElements &GetRoleAttrBase()const					{ return m_nCharAttrBase; };

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RoleAttr)
		const FCharacterBaseInfo &GetRoleBaseInfo()const			{ return m_fHeroBaseInfo; };


	//character角色基础功能
protected:
	UFUNCTION(Server, Unreliable, WithValidation)
		void RPC_Server_Skill(int8 key);
	bool RPC_Server_Skill_Validate(int8 key);
	void RPC_Server_Skill_Implementation(int8 key);

public:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void DoJump();

	virtual void Landed(const FHitResult& Hit) override;

	/* Skill Bounding*/
	void OnKeyboard_Q()					{ GetRoleSkillComponent()->ResponseSkillkeyboard('Q'); }
	void OnKeyboard_E()					{ GetRoleSkillComponent()->ResponseSkillkeyboard('E'); }
	void OnKeyboard_R()					{ GetRoleSkillComponent()->ResponseSkillkeyboard('R'); }
	void OnKeyboard_Z()					{ GetRoleSkillComponent()->ResponseSkillkeyboard('Z'); }
	void OnKeyboard_C()					{ GetRoleSkillComponent()->ResponseSkillkeyboard('C'); }
	void OnKeyboard_F()					{ GetRoleSkillComponent()->LunchSkill(); }

	void MildAttack()					{}
	void SevereAttack()					{}

//战斗逻辑
public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly,Category = RoleSkill)
	void ConsumeHp(int32 value);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly,Category = RoleSkill)
	void ConsumeMp(int32 value);

	UFUNCTION(BlueprintCallable, Category = RoleSkill)
	void OnSkillEnd();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RoleSkill)
	USKillComponent * GetRoleSkillComponent() const {	return CharacterSkillComponent;};

	//动画
	UFUNCTION(NetMulticast, Reliable)
		void RPC_Muitcast_PlaySkillMontage(UAnimMontage *SkillMontage);
	void RPC_Muitcast_PlaySkillMontage_Implementation(UAnimMontage *SkillMontage);
};
