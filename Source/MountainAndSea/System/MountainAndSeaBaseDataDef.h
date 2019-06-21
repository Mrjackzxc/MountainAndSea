#pragma once
#include "ObjectMacros.h"
#include "Engine/DataTable.h"
#include "MountainAndSeaBaseDataDef.generated.h"


UENUM(BlueprintType)
enum WorldBaseElement
{
	Base_Element_None,
	Base_Element_Metal,
	Base_Element_Wood,
	Base_Element_Water,
	Base_Element_Fire,
	Base_Element_Earth
};

USTRUCT(BlueprintType)
struct FStringLang:public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Id;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Content;
public:
	FString GetTableName()
	{
		return TEXT("StringLang.StringLang");
	}
};

template<class K,class V>
struct FKVData
{
	K m_Key;
	V m_Value;
};
