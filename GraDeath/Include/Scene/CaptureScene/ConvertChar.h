// ************************************************************
// fliename	ConvertChar.h
// brief	文字列の変換
// name		川口　裕
// memo
// 2013.08.20
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_CONVERT_CHAR_H_
#define	_CONVERT_CHAR_H_

// インクルード ***********************************************
#include <locale.h>


// ************************************************************
// ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換
//
// variable
// char*			: in_name			: 変換前文字列
// size_t			: size				: 文字列の長さ
// wchar_t*			: out_name			: 変換後文字列
// ************************************************************
extern size_t ConvertWChar(const char* in_name, size_t size, wchar_t* out_name);

// ************************************************************
// マルチバイト文字列(char*)をワイド文字列(WCHAR*)に変換
//
// variable
// wchar_t*			: in_name			: 変換前文字列
// size_t			: size				: 文字列の長さ
// char*			: out_name			: 変換後文字列
// ************************************************************
extern size_t ConvertChar(const wchar_t* in_name, size_t size, char* out_name);

#endif