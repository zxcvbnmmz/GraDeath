// ************************************************************
// fliename	CwnSkinMesh.cpp
// brief	独自フォーマットスキンメッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Graphic/D3DGraphic.h"
#include "Model/CwnSkinMesh.h"
#include "Model/CwnDecoder.h"
//#include "Shader.h"
//#include "Model/ModelSkinShader.h"
#include "Model/MeshDef.h"

#include "Graphic/Sampler/Sampler.h"
#include "Graphic/ShaderResource/ShaderResource.h"


// コンストラクタ
CwnSkinMesh::CwnSkinMesh() : bindBone( 0 ), nowBone( 0 ), animeData( 0 )
{
	animeFrame = 0;
}

// デストラクタ
CwnSkinMesh::~CwnSkinMesh()
{
}

void CwnSkinMesh::SetAnimeData( AnimeData* inData )
{
	animeData	= inData;
	animeFrame	= animeData->animeStart;
}

// 描画
void CwnSkinMesh::Render( Shader* shader, ModelSkinConstantBuffer* fscb )
{
	if ( !meshData ) return;

	int tempNumMesh = meshData->numMesh < (unsigned)animeData->numMesh ? meshData->numMesh : (unsigned)animeData->numMesh;
	//for ( DWORD num = 0; num < meshData->numMesh; num++ )
	for ( int num = 0; num < tempNumMesh; num++ )
	{
		SubRender( num, meshData->meshs[ num ], shader, fscb );
	}
}

// サブ描画
void CwnSkinMesh::SubRender( int num, CwnMesh& mesh, Shader* shader, ModelSkinConstantBuffer* fscb )
{
	//ModelSkinConstantBuffer temp;
	// シェーダーに渡すためのメンバ変数にコピー
	for ( DWORD j = 0; j < animeData->animes[ num ].numBone; j++ )
	{
		// 行列取得
		D3DXMATRIX mat = GetCurrentPoseMatrix( num, j, animeFrame * animeData->animes[ num ].numBone + j );

		// シェーダーに渡すので転置行列とする
		D3DXMatrixTranspose( &mat, &mat );

		// 行列をコピー
		//fscb->bone[ j ] = mat;
	}
	// 頂点バッファをセット
	mesh.vertexBuffer.SetToIA();
	// インデックスバッファをセット
	mesh.indexBuffer.SetToIA ();

	Sampler sampler;

	for ( DWORD i = 0; i < mesh.numMaterial; i++ )
	{	
		//shader->SetConstantBuffer( fscb );

		if ( mesh.material[ mesh.subSet[ i ].matIndex ].m_texture != NULL )
		{
			// サンプリングステートを渡す
			sampler.SetLinearWrap ();

			// テクスチャを渡す
			meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture->SetToShader ( 0, 1 );
		}

		// プリミティブ・トポロジーを設定
		Graphic::D3D::IA::SetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// マテリアルの各要素をエフェクトに渡す
		Graphic::D3D::Draw (
			mesh.subSet[ i ].faceCount,
			mesh.subSet[ i ].faceStart,
			0 );
	}
}

// 現在の姿勢行列を取得
D3DXMATRIX CwnSkinMesh::GetCurrentPoseMatrix ( int num, int bindIndex, int nowIndex )
{
	D3DXMATRIX inv;

	//	FBXのバインドポーズの逆行列を取得
	D3DXMatrixInverse( &inv, 0, &animeData->animes[ num ].bindPose[ bindIndex ] );

	// バインドポーズの逆行列とフレーム姿勢行列をかける。
	D3DXMATRIX ret = inv * animeData->animes[ num ].nowPose[ nowIndex ];

	return ret;
}

// アニメフレームの加算
void CwnSkinMesh::AddAnimeCount( int frame )
{
	animeFrame += frame;
	
	// スタートタイムを一時変更！！！！
	if ( animeFrame >= animeData->animeStop )
		animeFrame = animeData->animeStart;//animeCntStart;
}

// アニメフレームのセット
void CwnSkinMesh::SetAnimeCount( int frame )
{
	animeFrame = frame % animeData->animeStop;
}

// アニメーションカウントの終了確認
bool CwnSkinMesh::GetAnimeEnd()
{
	return animeFrame == ( animeData->animeStop - 1 );
}

int CwnSkinMesh::GetAnimeFrameEnd()
{
	return animeData->animeStop;
}