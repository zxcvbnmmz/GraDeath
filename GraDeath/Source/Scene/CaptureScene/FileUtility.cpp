// ************************************************************
// fliename	FileUtility.cpp
// brief	フォルダ内のファイル名の取得
// name		川口　裕
// memo
// 2013.08.20
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/FileUtility.h"
#include "Scene/CaptureScene/ConvertChar.h"


// フォルダ内のファイル名の取得
std::vector< std::string > ReadDirFileName(std::string folder)
{
	// 宣言
	std::vector< std::string > fileList;
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	// ファイル名検索のためにワイルドカード追加
	// 例 : "D:\\Users\\Pictures\\*.*"
	std::stringstream ss;
	ss << folder;
	std::string::iterator itr = folder.end();
	itr--;
	if (*itr != '\\') ss << '\\';
	ss << "*.*";

	wchar_t path[MAX_PATH] = { 0 };
	// 半角フォルダの場合足りなくなるので1加算
	ConvertWChar(ss.str().c_str(), ss.str().size() + 1, path);
	hFind = FindFirstFile(path, &fd);

	// 検索失敗
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"ファイル名の取得に失敗しました", L"error", MB_OK);
		fileList.clear();
		return fileList;//exit(1); // エラー終了
	}

	// ファイル名をリストに格納するためのループ
	do
	{
		// フォルダは除く
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			//ファイル名をリストに格納
			char file[256] = { 0 };// = fd.cFileName;
			ConvertChar(fd.cFileName, ss.str().size(), file);
			std::string str = file;
			fileList.push_back(str);
		}
	} while (FindNextFile(hFind, &fd)); //次のファイルを探索

	// hFindのクローズ
	FindClose(hFind);

	return fileList;
}
