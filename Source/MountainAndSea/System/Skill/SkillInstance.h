// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/CharBaseInfoDef.h"
#include "SkillDataDef.h"
#include "SkillInstance.generated.h"

UCLASS()
class MOUNTAINANDSEA_API ASkillInstance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillInstance(/*const FBaseElements & RoleBaseElement, const FSkillInstanceData & m_fSkillData*/);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//const FBaseElements m_fRoleBaseElement;
	//
	//const FSkillInstanceData m_fSkillData;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSkillEffict(UParticleSystem * SkillPartic);

	void InitSkill(FTransform startTransform);

};
