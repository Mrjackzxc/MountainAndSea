#pragma once
#include "System/TsingletonBase.h"
#include "JsonObject.h"
#include "SharedPointer.h"

template<typename T>
class CFileContrlller
{
public:
	CFileContrlller();
	~CFileContrlller();

public:

	static bool SaveFileToJson(const T & saveData);
	//if ture LoadFile be Success
	static bool LoadFileFromJson(T& eDataReader);

	static bool SaveFileToBinary(const T & saveData);

	static bool LoadFileFromBinary(T& eDataReader);
};

