// ************************************************************
// fliename	FileLoader.cpp
// brief	�t�@�C���̓Ǎ�
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/FileLoader.h"
#include "Scene/CaptureScene/FileUtility.h"
#include "Scene/CaptureScene/ConvertChar.h"


FileLoader::FileLoader()
{
}

FileLoader::~FileLoader()
{
}

void FileLoader::ModelLoad()
{
	if (!fileModelList.empty())
		fileModelList.clear();

	wchar_t inPath[MAX_PATH] = { 0 };
	char	inPath_c[MAX_PATH] = { 0 };

	GetFullPathName(L"Resource/Model", MAX_PATH, inPath, 0);
	ConvertChar(inPath, sizeof(inPath) / sizeof(inPath[0]), inPath_c);

	fileModelList = ReadDirFileName(inPath_c);
}

void FileLoader::AnimeLoad()
{
	if (!fileAnimeList.empty())
		fileAnimeList.clear();

	wchar_t inPath[MAX_PATH] = { 0 };
	char	inPath_c[MAX_PATH] = { 0 };

	GetFullPathName(L"Resource/Anime", MAX_PATH, inPath, 0);
	ConvertChar(inPath, sizeof(inPath) / sizeof(inPath[0]), inPath_c);

	fileAnimeList = ReadDirFileName(inPath_c);
}

std::vector< std::string > FileLoader::GetModelList()
{
	return fileModelList;
}

std::vector< std::string > FileLoader::GetAnimeList()
{
	return fileAnimeList;
}
