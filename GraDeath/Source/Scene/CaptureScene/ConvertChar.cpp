// ************************************************************
// fliename	ConvertChar.h
// brief	文字列の変換
// name		川口　裕
// memo
// 2013.08.20
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/ConvertChar.h"
#include <stdlib.h>


// ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換
size_t ConvertWChar(const char* in_name, size_t size, wchar_t* out_name)
{
	size_t len = 0;
	setlocale(LC_ALL, "japanese");
	mbstowcs_s(&len, out_name, size, in_name, _TRUNCATE);

	return len;
}

// マルチバイト文字列(char*)をワイド文字列(WCHAR*)に変換
size_t ConvertChar(const wchar_t* in_name, size_t size, char* out_name)
{
	size_t len = 0;
	setlocale(LC_ALL, "japanese");
	wcstombs_s(&len, out_name, size, in_name, _TRUNCATE);

	return len;
}