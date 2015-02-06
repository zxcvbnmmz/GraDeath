// ************************************************************
// fliename	FileUtility.h
// brief	フォルダ内のファイル名の取得
// name		川口　裕
// memo
// 2013.08.20
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_READDIRFILENAME_H_
#define	_READDIRFILENAME_H_

// インクルード ***********************************************
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>


// ************************************************************
// フォルダ内のファイル名の取得
//
// variable
// std::string		: folder			: フォルダ名
//
// return
// std::vector< std::string >			: ファイル名の配列
// ************************************************************
extern std::vector< std::string > ReadDirFileName(std::string folder);

#endif