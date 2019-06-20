#include "CFileContrlller.h"
#include "JsonSerializer.h"
#include "JsonWriter.h"
#include "FileHelper.h"
#include "Paths.h"


template<typename T>
CFileContrlller<T>::CFileContrlller()
{
}

template<typename T>
CFileContrlller<T>::~CFileContrlller()
{
}

template<typename T>
void CFileContrlller<T>::SaveFileToJson()
{
	TSharedRef<FJsonObject>  _pJsonRoot = MakeShareable(new FJsonObject);
	T::WriteJsonData(_pJsonRoot);
	FString _sStrGet;
	TSharedRef<TJsonWriter<TCHAR>> _tWriter = TJsonWriterFactory<>::Create(&_sStrGet);
	FJsonSerializer::Serialize(_pJsonRoot, _tWriter);
	FString sJsonPath = FPaths::GameConfigDir() + T::GetFileName()+FString(".json");
	FFileHelper::SaveStringToFile(_sStrGet, *sJsonPath);
}


template<typename T>
T CFileContrlller<T>::LoadFileFromJson()
{
	FString _sFilePath = FPaths::GameConfigDir() + T::GetFileName()+FString(".json");
	FString _sFileContent;
	FFileHelper::LoadFileToString(_sFileContent, *_sFilePath);
	TSharedRef<TJsonReader<TCHAR>> tReader = TJsonReaderFactory<>::Create(_sFileContent);
	TSharedPtr<FJsonObject> aJsonContent;
	FJsonSerializer::Deserialize(tReader, aJsonContent);
	return T::CreateDataFormJson(aJsonContent);
}

