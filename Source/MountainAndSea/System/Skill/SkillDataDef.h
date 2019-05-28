#pragma once
#include "ObjectMacros.h"
#include "Engine/DataTable.h"
#include "Particles/ParticleSystem.h"
#include "Animation/AnimMontage.h"
#include "SkillDataDef.generated.h"

UENUM()
enum ESkillType
{
	Skill_None,			//��Ч�ͼ���
	Skill_Directivity,	//ָ���ͼ���
	Skill_Range,		//��Χ�ͼ���
	SKill_Liner,		//���ͼ���
	Skill_Aided,		//������
};

UENUM()
enum ESkillPhaseEnum
{
	Phase_Prepare,//׼���׶�
	Phase_Playing,//���Ž׶�
	Phase_Ending,  //�����׶�
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
		TArray<FSkillPhaseStruct> PhaseStep;//���ܽ׶�
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
		int32 ContinueTime;//����ʱ��

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		int32 LoopTimes;//ѭ������

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		TArray<int32> EffectId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SKill)
		UParticleSystem* SkillEffect;//������Ч
public:
	static FString GetTableName()
	{
		return TEXT("SkillInstanceData.SkillInstanceData");
	}
};