//--------------------------------------------
// @filename	SizeGetter.h
// @outline		画像サイズ取得関数
// @auther		正田
//--------------------------------------------

//--------------------------------------------
// インクルードガード
//--------------------------------------------
#ifndef _SIZE_GETTER_H__
#define _SIZE_GETTER_H__

//--------------------------------------------
// インクルード
//--------------------------------------------
#include <D3DX10.h>

//--------------------------------------------
// @name
//  GetTextureSize(const char* fileName, D3DXVECTOR2* size)
// @param
//  const char* fileName	
//  D3DXVECTOR2* size		テクスチャサイズの格納先
// @todo
//  テクスチャのサイズを取得し格納する
//--------------------------------------------
extern void GetTextureSize(LPCWSTR fileName, D3DXVECTOR2*);

#endif	// end of SizeGetter