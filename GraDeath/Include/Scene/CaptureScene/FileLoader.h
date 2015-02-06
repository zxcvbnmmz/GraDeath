// ************************************************************
// filename	FileLoader.h
// brief	ファイルの読込
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _FILE_LOADER_H_
#define _FILE_LOADER_H_

// インクルード ***********************************************
#include <vector>
#include <string>

// ************************************************************
// class	FileLoader
// brief	ファイルの読込
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