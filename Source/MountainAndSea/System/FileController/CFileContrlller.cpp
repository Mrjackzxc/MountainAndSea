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
bool CFileContrlller<T>::SaveFileToJson(const T & saveData)
{
	TSharedRef<FJsonObject>  _pJsonRoot = MakeShareable(new FJsonObject);
	saveData.WriteJsonData(_pJsonRoot);
	FString _sStrGet;
	TSharedRef<TJsonWriter<TCHAR>> _tWriter = TJsonWriterFactory<>::Create(&_sStrGet);
	FJsonSerializer::Serialize(_pJsonRoot, _tWriter);
	FString sJsonPath = FPaths::GameConfigDir() + T::GetFileName()+FString(".json");
	FFileHelper::SaveStringToFile(_sStrGet, *sJsonPath);
}


template<typename T>
bool CFileContrlller<T>::LoadFileFromJson(T& eDataReader)
{
	FString _sFilePath = FPaths::GameConfigDir() + T::GetFileName()+FString(".json");
	FString _sFileContent;
	FFileHelper::LoadFileToString(_sFileContent, *_sFilePath);
	TSharedRef<TJsonReader<TCHAR>> tReader = TJsonReaderFactory<>::Create(_sFileContent);
	TSharedPtr<FJsonObject> aJsonContent;
	FJsonSerializer::Deserialize(tReader, aJsonContent);
	return eDataReader.ReadDataFormJson(aJsonContent);
}

template<typename T>
bool CFileContrlller<T>::SaveFileToBinary(const T & saveData)
{
	FString _sFilePath = FPaths::GameConfigDir() + T::GetFileName() + FString(".bin");
	FBufferArchive _eToBinary;
	saveData.WriteContentToBinary(_eToBinary);

	TArray<uint8> _aCompressedData;
	FArchiveSaveCompressedProxy _eCompressor(_aCompressedData, ECompressionFlags::COMPRESS_ZLIB);
	_eCompressor << _eToBinary;
	_eCompressor.Flush();

	if (!FFileHelper::SaveArrayToFile(CompressedData, *_sFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("--- FFILEHELPER:>> Invalid File"));
		return false;
	}
	// Free Binary Arrays 
	_eCompressor.FlushCache();
	_aCompressedData.Empty();

	_eToBinary.FlushCache();
	_eToBinary.Empty();

	// Close Buffer 
	_eToBinary.Close();
	return ;
}

template<typename T>
bool CFileContrlller<T>::LoadFileFromBinary(T& eDataReader)
{
	FString _sFilePath = FPaths::GameConfigDir() + T::GetFileName() + FString(".bin");
	TArray<uint8> _aCompressedData;
	if (!FFileHelper::LoadFileToArray(_aCompressedData, *_sFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("--- FFILEHELPER:>> Invalid File"))
		return eDataReader.ReadDataFromBinary();
	}
	FArchiveLoadCompressedProxy _eCompressor(_aCompressedData, ECompressionFlags::COMPRESS_ZLIB);
	FBufferArchive _eFromBinary;
	_eCompressor << _eFromBinary;

	FMemoryReader _eFromBinary = FMemoryReader(_eFromBinary, true);
	_eFromBinary.Seek(0);

	return eDataReader.ReadDataFromBinary(_eFromBinary);
}
