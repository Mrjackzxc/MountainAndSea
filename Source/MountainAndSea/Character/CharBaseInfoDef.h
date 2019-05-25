// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharBaseInfoDef.generated.h"



UENUM(BlueprintType)
enum ECharBaseStat
{
	InValidStat ,
	IdleStat=1,
	JumpStat=1<<1,
	CombatStat = 1 << 2,
	SKillStat = 1 << 3,
	UsepropStat =1 << 4,
	ControlStat=1 << 5,
	StatMax
};

UENUM(BlueprintType)
enum EControlStat
{
	None,
	StunStat=1,
	Floating=1<<1,
	HitBack=1<<2,
};

UENUM(BlueprintType)
enum EBuff
{
	NoBuff
};

UENUM(BlueprintType)
enum ECharAnimStatType
{
	UpperBled,
	WholeBlend
};

USTRUCT(BlueprintType)
struct FBaseElements
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, Category = "BaseElement")
		int32 m_nMetal;

	UPROPERTY(BlueprintReadWrite, Category = "BaseElement")
		int32 m_nWood;

	UPROPERTY(BlueprintReadWrite, Category = "BaseElement")
		int32 m_nWater;

	UPROPERTY(BlueprintReadWrite, Category = "BaseElement")
		int32 m_nFire;

	UPROPERTY(BlueprintReadWrite, Category = "BaseElement")
		int32 m_nEarth;

};

USTRUCT(BlueprintType)
struct FCharacterBaseInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nHeroHP;

	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nHeroMP;

	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nLevel;

	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nNormalAttack;

	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nNormalDefence;

	UPROPERTY(BlueprintReadWrite, Category = "CharBaseInfo")
		int32 m_nAccurate;

};



UCLASS()
class MOUNTAINANDSEA_API ACharBaseInfoDef : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharBaseInfoDef();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
