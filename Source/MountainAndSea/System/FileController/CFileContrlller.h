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
	static void SaveFileToJson();

	static T LoadFileFromJson();
};

