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

UENUM(BlueprintType)
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
		TMap<int32,FSkillPhaseStruct> PhaseStep;//���ܽ׶�
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
		int32 ContinueTime;//����ʱ��

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		int32 LoopTimes;//ѭ������

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		float SkillSpeed;//ѭ������

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SKill)
		UParticleSystem* SkillEffect;//������Ч
public:
	static FString GetTableName()
	{
		return TEXT("SkillInstanceData.SkillInstanceData");
	}
};