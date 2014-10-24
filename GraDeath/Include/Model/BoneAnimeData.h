// ************************************************************
// filename	BoneAnimeData.h
// brief	独自フォーマットアニメーション行列の取得
// name		川口　裕
// memo
// 2013.09.13
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_BONE_ANIME_DATA_H_
#define	_BONE_ANIME_DATA_H_

// インクルード ***********************************************
#include <vector>
#include "Model/MeshDef.h"


// 前方宣言 ***************************************************
struct CwnMatrix;


// ************************************************************
// class	BoneAnimeData
// brief	独自フォーマットアニメーション行列の取得
// ************************************************************
class BoneAnimeData{
private:
	std::vector< AnimeData* >	animeArray;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	BoneAnimeData();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~BoneAnimeData();

	// ************************************************************
	// 解放
	// ************************************************************
	void Release();

	// ************************************************************
	// アニメーションデータの読込
	// ************************************************************
	bool LoadAnime( char* filename );

	// ************************************************************
	// 固定行列の取得
	// ************************************************************
	//Matrix* GetAnimeBindMatrix( int num );

	// ************************************************************
	// アニメーション行列の取得
	// ************************************************************
	//Matrix* GetAnimeNowMatrix( int num );

	// ************************************************************
	// アニメーションデータの取得
	// ************************************************************
	AnimeData* GetAnimeData( int num );

	// ************************************************************
	// アニメーションの開始カウントの取得
	// ************************************************************
	int GetAnimeStartCount( int num );

	// ************************************************************
	// アニメーションの終了カウントの取得
	// ************************************************************
	int GetAnimeEndCount( int num );

	// ************************************************************
	// 各アニメーション配列のコピー
	// ************************************************************
	void CopyAnimeData( BoneAnimeData* setAnimeData );	

	// ************************************************************
	// アニメーションの追加
	// ************************************************************
	void PushAnimation( AnimeData* _anime );

private:
	// ************************************************************
	// ボーン行列の読込
	// ************************************************************
	void LoadBone( CwnMatrix* bindBone, CwnMatrix* nowBone, AnimeData* animeData, int num );

	// ************************************************************
	// 行列のコピー
	// ************************************************************
	void CopyMatrix ( CwnMatrix& inMat, D3DXMATRIX& outMat );

	// ************************************************************
	// 現在の姿勢行列を取得
	// ************************************************************
	//Matrix GetCurrentPoseMatrix( int num, int bindIndex, int nowIndex );

	// ************************************************************
	// 現在のアニメーションデータ配列を取得
	// ************************************************************
	std::vector< AnimeData* >* GetAnimeArray();

};


// アニメーションデータの取得
inline AnimeData* BoneAnimeData::GetAnimeData( int num )
{
	return animeArray[ num ];
}

// アニメーションの開始カウントの取得
inline int BoneAnimeData::GetAnimeStartCount( int num )
{
	return animeArray[ num ]->animeStart;
}

// アニメーションの終了カウントの取得
inline int BoneAnimeData::GetAnimeEndCount( int num )
{
	return animeArray[ num ]->animeStop;
}

#endif