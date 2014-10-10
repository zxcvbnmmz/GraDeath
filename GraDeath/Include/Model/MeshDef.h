// ************************************************************
// fliename	FBXDef.h
// brief	FBX静的シェーダ
// name		川口　裕
// memo
// 2013.06.11
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_MESH_DEF_H_
#define	_MESH_DEF_H_

//#define FBXSDK_NEW_API

// インクルード ***********************************************
#include <D3DX10math.h>
//#include "Core.h"
//#include "Typedefs.h"
//#include "Texture.h"
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"

// 前方宣言 ***************************************************
namespace Graphic
{
	class ShaderResource;
}

// Graphicの仕様宣言 ******************************************
using namespace Graphic;


// ************************************************************
// struct	MeshVertex
// brief	メッシュ頂点構造体
//
// variable
// Vector3			: pos				: 位置
// Vector3			: normal			: 法線
// Vector2			: uv				: UV座標
// UINT				: boneIndex[4]		: ボーン番号
// float			: boneWeight[4]		: ボーンの重み
// ************************************************************ 
struct MeshVertex
{
	D3DXVECTOR3	pos;
	D3DXVECTOR3	normal;
	D3DXVECTOR3	uv;
	UINT		boneIndex[ 4 ];
	float		boneWeight[ 4 ];

	MeshVertex()
	{
		ZeroMemory( this, sizeof( MeshVertex ) );
	}
};

// ************************************************************
// struct	MeshBone
// brief	ボーン構造体
//
// variable
// Matrix			: bindPose			: 固定しているポーズ
// Matrix			: nowPose			: 現在のポーズ
// ************************************************************
struct MeshBone
{
	D3DXMATRIX	bindPose;
	D3DXMATRIX	nowPose;

	MeshBone()
	{
		ZeroMemory( this, sizeof( MeshBone ) );
	}
};

// ************************************************************
// struct	MeshSubSet
// brief	メッシュのサブセット
//
// variable
// UINT				: matIndex			: ポリゴン番号 
// UINT				: faceStart			: 3つの頂点のうち、何番目か
// UINT				: faceCount			: 属しているポリゴン数
// ************************************************************
struct MeshSubSet
{
	unsigned int matIndex;
	unsigned int faceStart;
	unsigned int faceCount;

	MeshSubSet()
	{
		ZeroMemory( this, sizeof( MeshSubSet ) );
	}
};

// ************************************************************
// struct	MeshMaterial
// brief	マテリアル構造体
//
// variable
// Vector4			: ambient			: アンビエント
// Vector4			: diffuse			: ディフューズ
// Vector4			: specular			: スペキュラ
// float			: alpha				: 透過
// float			: power				: 光沢
// DWORD			: dwNumFace;		: マテリアルの持っているポリゴン数
// Texture			: m_texture;		: テクスチャ
// wchar_t			: textureName[100]	: テクスチャの名前
// char				: matName[256]		: マテリアルの名前
// ************************************************************
struct MeshMaterial
{
	D3DXVECTOR4			ambient;			// アンビエント
	D3DXVECTOR4			diffuse;			// ディフューズ
	D3DXVECTOR4			specular;			// スペキュラ
	float				alpha;				// 透過
	float				power;				// 光沢
	unsigned long		dwNumFace;			// マテリアルの持っているポリゴン数

	ShaderResource*		m_texture;			// テクスチャ
	
	wchar_t				textureName[ 20 ];	// テクスチャの名前
	char				matName[ 20 ];		// マテリアルの名前

	MeshMaterial()
	{
		ZeroMemory( this, sizeof( MeshMaterial ) );
	}
};

// ************************************************************
// struct	Mesh
// brief	メッシュ構造体
//
// variable
// DWORD			: numVert			: 頂点数
// DWORD			: numFace			: 面数
// DWORD			: numUV				: UV数
// DWORD			: numMaterial		: マテリアル数
// DWORD			: numSub			: サブセットの数
// DWORD			: numChild			: 子供数
// Mesh**			: childMesh			: 子のメッシュ
// FbxNode*			: node				: ノードデータ
// VertexBuffer		: vertexBuffer		: 頂点バッファ
// IndexBuffer*		: indexBuffer		: インデックスバッファ
// MeshMaterial*	: material;			: マテリアル
// MeshSubSet*		: subSet;			: サブセット
// Matrix			: parentOrientation	: 親の姿勢行列
// Matrix			: world;			: メッシュの最終的なワールド行列
// Matrix			: orientation;		: 姿勢行列
// int				: numBone;			: ボーン数
// MeshBone*		: boneArray;		: 独自ボーンデータ配列
// FbxCluster**		: cluster;			: クラスター
// Matrix			: boneData[255]		: シェーダーに渡すためのボーン配列
// ************************************************************
//struct Mesh
//{
//	// メッシュ関連
//	unsigned long			numVert;
//	unsigned long			numFace;
//	unsigned long			numUV;
//	unsigned long			numMaterial;
//	unsigned long			numSub;
//	unsigned long			numChild;
//
//	// メッシュ関連
//	Mesh**			childMesh;
//
//	// バッファ関連
//	//VertexBuffer	vertexBuffer;
//	//IndexBuffer*	indexBuffer;
//
//	// マテリアル関連
//	MeshMaterial*	material;
//	MeshSubSet*		subSet;
//	
//	//	行列関連
//	D3DXMATRIX		parentOrientation;
//	D3DXMATRIX		world;
//	D3DXMATRIX		orientation;
//
//
//	// FBX関連
//	int				numBone;
//	MeshBone*		boneArray;
//	D3DXMATRIX		boneData[ 255 ];
//
//};

// ************************************************************
// 独自用メッシュ
// brief	独自用メッシュの構造体
// ************************************************************
struct CwnMesh
{
	// メッシュ関連
	unsigned long			numVert;		// バーテックス数
	unsigned long			numFace;		// 面数
	unsigned long			numMaterial;	// マテリアル数
	unsigned long			numSub;			// サブセット数

	// バッファ関連
	//VertexBuffer	vertexBuffer;	// 頂点バッファ
	//IndexBuffer		indexBuffer;	// インデックスバッファ

	MeshVertex*		vertexList;		// ベーテックスリスト
	int*			indexList;		// インデックスリスト

	MeshMaterial*	material;		// マテリアル数
	MeshSubSet*		subSet;			// サブセット数

	// ************************************************************
	// コンストラクタ
	// ************************************************************
	CwnMesh() : material( 0 ), subSet( 0 ){}
};

// ************************************************************
// 独自用メッシュデータ
// brief	独自用メッシュデータの構造体
// ************************************************************
struct MeshData
{
	char			modelName[ 20 ];	// モデル名
	unsigned long	numMesh;			// メッシュ数
	unsigned long	numBone;			// ボーン数
	int				animeStart;			// アニメフレームの開始
	int				animeStop;			// アニメフレームの終わり

	CwnMesh*		meshs;				// メッシュの動的配列

	// ************************************************************
	// コンストラクタ
	// ************************************************************
	MeshData() : meshs( 0 ){}
};

// ************************************************************
// struct	AnimeData
// brief	アニメーションデータの構造体
// ************************************************************
struct CwnAnime
{
	unsigned long	numBone;

	D3DXMATRIX*		bindPose;
	D3DXMATRIX*		nowPose;

};

// ************************************************************
// struct	AnimeData
// brief	アニメーションデータの構造体
// ************************************************************
struct AnimeData
{
	int		animeStart;
	int		animeStop;
	int		numMesh;

	CwnAnime* animes;

	AnimeData() :  animes( 0 ){}
};

// ************************************************************
// メッシュテクスチャ入れ替え用構造体
// brief	メッシュテクスチャ入れ替え用
// ************************************************************
struct MeshTexture
{
	unsigned long		numMat;
	ShaderResource*		texture;

	// ************************************************************
	// コンストラクタ
	// ************************************************************
	MeshTexture() : texture( 0 ){}
};

// ************************************************************
// テクスチャアタッチ構造体
// brief	メッシュテクスチャ入れ替え用
// ************************************************************
struct MeshTextures
{
	unsigned long	numMesh;
	MeshTexture*	texData;

	// ************************************************************
	// コンストラクタ
	// ************************************************************
	MeshTextures() : texData( 0 ){}
};

namespace ModelTexture
{

// ************************************************************
// テクスチャアタッチ構造体の生成
// brief テクスチャは生成しない
// ************************************************************
extern void CreateMeshTextures( MeshTextures* outTextures, const MeshData* inData );

// ************************************************************
// テクスチャアタッチ構造体の解放
// ************************************************************
extern void DeleteMeshTextures( MeshTextures* textures );

}

#endif