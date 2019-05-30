#pragma once
#include "../TsingletonBase.h"
#include "Engine/DataTable.h"

template <typename DataType>
class CTableWrapper
{
private:
	CTableWrapper();
	CTableWrapper(const CTableWrapper & other);
	CTableWrapper & operator=(const CTableWrapper & other);

public:

	static UDataTable * GetTable()
	{
		static UDataTable * s_pTable = NULL;
		if (s_pTable == NULL)
		{
			FString InName("DataTable'/Game/MountainAndSea/DataTable/");
			InName += DataType::GetTableName();
			InName += TEXT("'"); 
			s_pTable = (UDataTable*)::StaticLoadObject(UDataTable::StaticClass(), nullptr, *InName);
			if (s_pTable != NULL)
				s_pTable->AddToRoot();
		}
		return s_pTable;
	}

	static const DataType * GetItem(int32 nKeyId)
	{
		UDataTable * pTable = GetTable();
		if (pTable != NULL)
		{
			return  pTable->FindRow<DataType>(*FString::FromInt(nKeyId), DataType::GetTableName());
		}
		return NULL;
	}
};