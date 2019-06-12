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

UENUM(BlueprintType)
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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 SkillPhase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 ContinueTime;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		TArray<int32> EffectId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		UAnimMontage * SkillAnimMontage;
};


USTRUCT(BlueprintType)
struct FSkillDataBase:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category=SKill)
		int32 Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 Level;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 PropertyType;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 Cd;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 ConsumeMp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 SKillNameId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 SkillType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		bool CanMove;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		bool BeCancel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 SkillInstanceId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		TMap<int32,FSkillPhaseStruct> PhaseStep;//技能阶段
public:
	static FString GetTableName()
	{
		return TEXT("SkillDataBase.SkillDataBase");
	}
};

class ASkillInstance;

USTRUCT(BlueprintType)
struct FSkillInstanceData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		TSubclassOf<AActor> SkillType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 EffectNameId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 EffectType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 ContinueTime;//持续时间

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 LoopTimes;//循环次数

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		float SkillSpeed;//循环次数

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		UParticleSystem* SkillEffect;//技能特效
public:
	static FString GetTableName()
	{
		return TEXT("SkillInstanceData.SkillInstanceData");
	}
};