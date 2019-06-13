// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/CharBaseInfoDef.h"
#include "SkillDataDef.h"
#include "Particles/ParticleSystemComponent.h"
#include "SkillInstance.generated.h"

UCLASS()
class MOUNTAINANDSEA_API ASkillInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FBaseElements m_fRoleBaseElement;

	FSkillInstanceData m_fSkillData;

	UParticleSystemComponent * m_pSkillComponent;

protected:
	void SetLiveTime(float nLiveTime) ;

	void DestroySkill() { Destroy(); }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSkillEffict(UParticleSystem * SkillPartic);

	void InitSkill(const FBaseElements & RoleBaseElement, const FSkillInstanceData & SkillData,FTransform startTransform);

	UFUNCTION(NetMulticast, Reliable)
		void RPC_Multicast_InitSkill(const FBaseElements & RoleBaseElement, const FSkillInstanceData & SkillData, FTransform startTransform);
	void RPC_Multicast_InitSkill_Implementation(const FBaseElements & RoleBaseElement, const FSkillInstanceData & SkillData, FTransform startTransform);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Skill)
		void PlaySkill();
 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Skill)
		const FBaseElements GetRoleAttrBase()const			{ return m_fRoleBaseElement; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Skill)
		const FSkillInstanceData GetSkillData()const		{ return m_fSkillData; }
};
