// ************************************************************
// filename	FileLoader.h
// brief	�t�@�C���̓Ǎ�
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef _FILE_LOADER_H_
#define _FILE_LOADER_H_

// �C���N���[�h ***********************************************
#include <vector>
#include <string>

// ************************************************************
// class	FileLoader
// brief	�t�@�C���̓Ǎ�
// ************************************************************
class FileLoader{
private:
	std::vector< std::string > fileModelList;
	std::vector< std::string > fileAnimeList;

public:
	FileLoader();

	~FileLoader();

	void ModelLoad();

	void AnimeLoad();

	std::vector< std::string > GetModelList();

	std::vector< std::string > GetAnimeList();

};

#endif