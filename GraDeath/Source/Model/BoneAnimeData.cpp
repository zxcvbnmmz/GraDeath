// ************************************************************
// filename	BoneAnimeData.cpp
// brief	独自フォーマットアニメーション行列の取得
// name		川口　裕
// memo
// 2013.09.13
// ************************************************************

// インクルード ***********************************************
#include "Model/BoneAnimeData.h"
#include "Utility/SafeDelete.h"
#include <fstream>


// ************************************************************
// struct	CwnMatrix
// brief	読込用簡易行列
// ************************************************************
struct CwnMatrix
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

// コンストラクタ
BoneAnimeData::BoneAnimeData(){}

// デストラクタ
BoneAnimeData::~BoneAnimeData()
{
	animeArray.clear();
	//Release();
}

// 解放
void BoneAnimeData::Release()
{
	// 空だと行わない
	if ( animeArray.empty() )
		return;

	std::vector< AnimeData* >::iterator cur = animeArray.begin();

	while ( cur != animeArray.end() )
	{
		if ( ( *cur ) != NULL )
		{
			for ( DWORD num = 0; num < (unsigned)( *cur )->numMesh; num++ )
			{
				Util::safeDeleteArray ( ( *cur )->animes[ num ].bindPose );
				Util::safeDeleteArray ( ( *cur )->animes[ num ].nowPose );
			}
			Util::safeDeleteArray ( ( *cur )->animes );
			delete *cur;
			cur = animeArray.erase( cur );
			continue;
		}
		++cur;
	}
}

// アニメーションデータの読込
bool BoneAnimeData::LoadAnime( char* filename )
{
	std::ifstream ifs( filename, std::ios::binary );

	if( ifs.fail() ) return false;

	AnimeData* tempData = new AnimeData;

	// メッシュ数の取得
	ifs.read( ( char* )&tempData->numMesh, sizeof( DWORD ) );

	// アニメーションのフレーム数の最初と最後の取得
	DWORD startTime, stopTime;
	ifs.read( ( char* )&startTime, sizeof( DWORD ) );
	ifs.read( ( char* )&stopTime, sizeof( DWORD ) );
	tempData->animeStart	= ( int )startTime;
	tempData->animeStop	= ( int )stopTime;

	// メッシュ分行列を作成
	tempData->animes = new CwnAnime[ tempData->numMesh ];

	// メッシュ分の姿勢行列を生成
	for ( int num = 0; num < tempData->numMesh; num++ )
	{
		// ボーン情報取得
		ifs.read( ( char* )&tempData->animes[ num ].numBone, sizeof( DWORD ) );

		CwnMatrix* bindBone	= 0;
		CwnMatrix* nowBone	= 0;

		// バインド行列
		bindBone = new CwnMatrix[ tempData->animes[ num ].numBone ];
		ifs.read( ( char* )bindBone, sizeof( CwnMatrix ) * tempData->animes[ num ].numBone );

		// 姿勢行列
		nowBone = new CwnMatrix[ tempData->animes[ num ].numBone * tempData->animeStop ];
		ifs.read( ( char* )nowBone, sizeof( CwnMatrix ) * tempData->animes[ num ].numBone * tempData->animeStop );

		// ボーンの読込
		LoadBone( bindBone, nowBone, tempData, num );

		delete[] bindBone;
		delete[] nowBone;
	}

	animeArray.push_back( tempData );

	return true;
}

// ボーン行列の読込
void BoneAnimeData::LoadBone( CwnMatrix* bindBone, CwnMatrix* nowBone, AnimeData* animeData, int num )
{
	animeData->animes[ num ].bindPose = new D3DXMATRIX[ animeData->animes[ num ].numBone ];

	for ( DWORD i = 0; i < animeData->animes[ num ].numBone; i++ )
	{
		CopyMatrix( bindBone[ i ], animeData->animes[ num ].bindPose[ i ] );
	}

	animeData->animes[ num ].nowPose = new D3DXMATRIX[ animeData->animes[ num ].numBone * animeData->animeStop ];

	for ( int cnt = 0; cnt < animeData->animeStop; cnt++ )
	{
		// ボーンの数分ループ実行
		for ( DWORD i = 0; i < animeData->animes[ num ].numBone; i++ )
		{
			CopyMatrix( nowBone[ cnt * animeData->animes[ num ].numBone + i ], animeData->animes[ num ].nowPose[ cnt * animeData->animes[ num ].numBone + i ] );
		}
	}
}

// 行列のコピー
void BoneAnimeData::CopyMatrix ( CwnMatrix& inMat, D3DXMATRIX& outMat )
{
	outMat._11 = inMat._11; outMat._12 = inMat._12; outMat._13 = inMat._13; outMat._14 = inMat._14;
	outMat._21 = inMat._21; outMat._22 = inMat._22; outMat._23 = inMat._23; outMat._24 = inMat._24;
	outMat._31 = inMat._31; outMat._32 = inMat._32; outMat._33 = inMat._33; outMat._34 = inMat._34;
	outMat._41 = inMat._41; outMat._42 = inMat._42; outMat._43 = inMat._43; outMat._44 = inMat._44;
}

// 各アニメーション配列のコピー
void BoneAnimeData::CopyAnimeData( BoneAnimeData* setBoneAnimeData )
{
	Release();

	std::vector< AnimeData* >* tempArray = setBoneAnimeData->GetAnimeArray();
	int size = tempArray->size();
	animeArray.resize( size );

	for ( int i = 0; i < size; i++ )
	{
		animeArray[ i ] = ( *tempArray )[ i ];
	}
}

// 現在のアニメーションデータ配列を取得
std::vector< AnimeData* >* BoneAnimeData::GetAnimeArray()
{
	return &animeArray;
}

// アニメーションの追加
void BoneAnimeData::PushAnimation( AnimeData* _anime )
{
	animeArray.push_back( _anime );
}