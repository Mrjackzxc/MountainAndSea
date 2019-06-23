#pragma once
#include "System/Skill/SkillDataDef.h"
#include "System/MountainAndSeaBaseDataDef.h"
#include "BufferArchive.h"

#define SELECT_ELEMENT_MAX 3

class  USKillComponent;

struct FSelectElementStack
{
public:
	FSelectElementStack() :m_nSelectElement{ 0 }
	{

	}
private:
	int32 m_nSelectElement[SELECT_ELEMENT_MAX];
public:
	void add(int32 newElement)
	{
		bool _addSuccess = false;
		for (size_t i = 0; i < SELECT_ELEMENT_MAX; i++)
		{
			if (m_nSelectElement[i] == 0)
			{
				m_nSelectElement[i] = newElement;
				_addSuccess = true;
				break;
			}
		}if (!_addSuccess)
		{
			for (size_t i = 0; i < SELECT_ELEMENT_MAX-1; i++)
			{
				m_nSelectElement[i] = m_nSelectElement[i + 1];
			}
			m_nSelectElement[2] = newElement;
		}
	}

	int32 GetElement(int32 idx) const 
	{
		if (idx<0||idx>= SELECT_ELEMENT_MAX)
		{
			return 0;
		}
		return m_nSelectElement[idx];
	}

	int32 getKey() const 
	{
		int32 _result = 0;
		for (size_t i=0;i< SELECT_ELEMENT_MAX;i++)
		{	
			_result+=GetElement(0)*FMath::Pow(10, SELECT_ELEMENT_MAX-i);
		}
		return _result;
	}

	void reset()
	{
		for (size_t i=0;i< SELECT_ELEMENT_MAX;i++)
		{
			m_nSelectElement[i] = 0;
		}
	}
};

struct FSkillLearnMap
{
	int32 nSkillId;
	int32 nSkillLevel;
	bool bIsLearnSkill;
};

struct FSkillConfigReader
{
	FKVData<int8, int32> ReadData[5];

	bool ReadDataFromBinary(FBufferArchive& eReadData)
	{
		eReadData<<ReadData[0].m_Key;
		eReadData<<ReadData[0].m_Value;
		eReadData<<ReadData[1].m_Key;
		eReadData<<ReadData[1].m_Value;
		eReadData<<ReadData[2].m_Key;
		eReadData<<ReadData[2].m_Value;
		eReadData<<ReadData[3].m_Key;
		eReadData<<ReadData[3].m_Value;
		eReadData<<ReadData[4].m_Key;
		eReadData<<ReadData[4].m_Value; 
		return true;
	}

	bool ReadDataFromBinary()
	{
		ReadData[0].m_Key='Q';
		ReadData[0].m_Value=0;
		ReadData[1].m_Key = 'E';
		ReadData[1].m_Value = 0;
		ReadData[2].m_Key = 'R';
		ReadData[2].m_Value = 0;
		ReadData[3].m_Key = 'Z';
		ReadData[3].m_Value = 0;
		ReadData[4].m_Key = 'X';
		ReadData[4].m_Value = 0;
		return false;
	}

	void RevetToMap(TMap<int8, int32> & outParam)
	{
		for (size_t i=0;i<5;i++)
		{
			outParam[ReadData[i].m_Key] = ReadData[i].m_Value;
		}
	}

};

struct FSkillConfigWriter
{
	FKVData<int8, int32> ReadData[5];

	void WriteDataFromBinary(FBufferArchive& eReadData)
	{
		eReadData << ReadData[0].m_Key;
		eReadData << ReadData[0].m_Value;
		eReadData << ReadData[1].m_Key;
		eReadData << ReadData[1].m_Value;
		eReadData << ReadData[2].m_Key;
		eReadData << ReadData[2].m_Value;
		eReadData << ReadData[3].m_Key;
		eReadData << ReadData[3].m_Value;
		eReadData << ReadData[4].m_Key;
		eReadData << ReadData[4].m_Value;
	}

	void ReadDataFromBinary()
	{
		ReadData[0].m_Key = 'Q';
		ReadData[0].m_Value = 0;
		ReadData[1].m_Key = 'E';
		ReadData[1].m_Value = 0;
		ReadData[2].m_Key = 'R';
		ReadData[2].m_Value = 0;
		ReadData[3].m_Key = 'Z';
		ReadData[3].m_Value = 0;
		ReadData[4].m_Key = 'X';
		ReadData[4].m_Value = 0;
	}

};

class ISkillConfirmInterface
{
public:
	ISkillConfirmInterface(USKillComponent * AttachTo);
	virtual ~ISkillConfirmInterface();

protected:
	USKillComponent * ParentComponent;

	TMap<int8,int32> SkillKeyValue;
	
	virtual void LoadConfig()=0;

	int32 GetSkillLevel()
	{
		//TODO:Read ConfigData To Get Skill Level
		return 0;
	}
public:

	virtual void OnSkillKeyBoardEnter(const int8 & key)=0;

	virtual const int32 GetSkillID() const = 0;

	virtual const FSkillDataBase * EnsureSkill(int32 nSkillID);

	virtual void LunchSkill();
};

class CSkillGroupConfirm:public ISkillConfirmInterface
{
public:
	CSkillGroupConfirm(USKillComponent * AttachTo);
	 ~CSkillGroupConfirm();
protected:
	FSelectElementStack m_SelectSkillGroup;

	void LoadConfig() override final;
public:
	void OnSkillKeyBoardEnter(const int8 & key) override final;

	virtual const int32 GetSkillID()const override final;
};

class CSkillSingleConfirm :public ISkillConfirmInterface
{
public:
	CSkillSingleConfirm(USKillComponent * AttachTo);
	~CSkillSingleConfirm();
protected:
	int32 m_nSelectSkillId;

	void LoadConfig() override;

public:
	void OnSkillKeyBoardEnter(const int8 & key) override;

	virtual const int32 GetSkillID()const override final;
};