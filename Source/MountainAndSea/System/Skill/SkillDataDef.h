#pragma once
#include "ObjectMacros.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystem.h"
#include "Animation/AnimMontage.h"
#include "SkillDataDef.generated.h"

UENUM()
enum ESkillType
{
	Skill_None,			//无效型技能
	Skill_Directivity,	//指向型技能
	Skill_Range,		//范围型技能
	SKill_Liner,		//线型技能
	Skill_Aided,		//辅助型
};

UENUM()
enum ESkillPhaseEnum
{
	Phase_Prepare,//准备阶段
	Phase_Playing,//播放阶段
	Phase_Ending,  //结束阶段
	Phase_Max
};

USTRUCT(BlueprintType)
struct FSkillPhaseStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 SkillPhase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 ContinueTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		TArray<int32> EffectId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		UAnimMontage * SkillAnimMontage;
};


USTRUCT(BlueprintType)
struct FSkillDataBase:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=SKill)
		int32 Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 PropertyType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 Cd;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 ConsumeMp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 SKillNameId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 SkillType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		bool CanMove=true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		bool BeCancel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		TArray<FSkillPhaseStruct> PhaseStep;//技能阶段
public:
	static FString GetTableName()
	{
		return TEXT("SkillDataBase.SkillDataBase");
	}
};

USTRUCT(BlueprintType)
struct FSkillInstanceData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 EffectNameId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 EffectType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 ContinueTime;//持续时间

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 LoopTimes;//循环次数

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		TArray<int32> EffectId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		UParticleSystem* SkillEffect;//技能特效
public:
	static FString GetTableName()
	{
		return TEXT("SkillInstanceData.SkillInstanceData");
	}
};