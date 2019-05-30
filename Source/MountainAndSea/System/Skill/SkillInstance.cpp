// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillInstance.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASkillInstance::ASkillInstance(/*const FBaseElements & RoleBaseElement, const FSkillInstanceData & SkillData*/)//:m_fRoleBaseElement(RoleBaseElement),m_fSkillData(SkillData)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillInstance::SetSkillEffict(UParticleSystem * SkillPartic)
{
	UGameplayStatics::SpawnEmitterAttached(SkillPartic, RootComponent, "None", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
}

void ASkillInstance::InitSkill(FTransform startTransform)
{

}

