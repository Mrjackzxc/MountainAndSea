// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillInstance.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Function.h"

// Sets default values

ASkillInstance::ASkillInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASkillInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillInstance::SetLiveTime(float nLiveTime)
{
	if (nLiveTime!=0)
	{
		FTimerHandle _TimerHandle;
		auto _Lambda = FTimerDelegate::CreateLambda([&]() {DestroySkill(); });
		GWorld->GetTimerManager().SetTimer(_TimerHandle, _Lambda,1.f,false, nLiveTime);
	}
}

// Called every frame
void ASkillInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillInstance::SetSkillEffict(UParticleSystem * SkillPartic)
{
	m_pSkillComponent = UGameplayStatics::SpawnEmitterAttached(SkillPartic, RootComponent, "None", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
}

void ASkillInstance::InitSkill(const FBaseElements & RoleBaseElement, const FSkillInstanceData & SkillData,FTransform startTransform)
{
	m_fSkillData = SkillData;
	m_fRoleBaseElement = RoleBaseElement;
	SetActorTransform(startTransform);
	SetSkillEffict(m_fSkillData.SkillEffect);
	SetLiveTime(SkillData.ContinueTime);
}

