// ************************************************************
// fliename	CwnBaseMesh.cpp
// brief	独自フォーマットベースメッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Model/CwnBaseMesh.h"
#include "Model/CwnDecoder.h"
#include "Model/MeshDef.h"
#include "Utility/SafeDelete.h"
#include "Graphic/ShaderResource/ShaderResource.h"



// コンストラクタ
CwnBaseMesh::CwnBaseMesh() : decoder( nullptr ), meshData( 0 ){}

// デストラクタ
CwnBaseMesh::~CwnBaseMesh()
{
	Release();
}

// 解放
void CwnBaseMesh::Release()
{
	Util::safeDelete ( decoder );
}

// 読込
bool CwnBaseMesh::LoadCwn( char* filename, char* path )
{
	// 既に作られていたら真を返す
	if ( decoder ) return true;

	decoder = new CwnDecoder;
	bool ret = decoder->LoadCwn( filename, path );

	if ( ret )
	{
		meshData = decoder->GetMesh();
	}
	return  ret;
}

// メッシュデータの取得
const MeshData* CwnBaseMesh::GetMesh()
{
	if ( !meshData )
		return nullptr;
	return meshData;
}

// テクスチャのアタッチ
bool CwnBaseMesh::SetAttachingTexture( const MeshTextures* textures )
{
	if ( !meshData ) 
		return false;

	if ( meshData->numMesh != textures->numMesh )
		return false;

	for ( unsigned long i = 0; i < meshData->numMesh; i++ )
	{
		if ( meshData->meshs[ i ].numMaterial != textures->texData[ i ].numMat )
			return false;

		for ( unsigned int k = 0; k < meshData->meshs[ i ].numMaterial; k++ )
		{
			meshData->meshs[ i ].material[ k ].m_texture = textures->texData[ i ].texture;
		}
	}
	return true;
}

bool CwnBaseMesh::SetAttachingTexture( Graphic::ShaderResource* inTexture )
{
	if ( !meshData )
		return false;

	for ( unsigned long i = 0; i < meshData->numMesh; i++ )
	{
		for ( unsigned int k = 0; k < meshData->meshs[ i ].numMaterial; k++ )
		{
			if ( meshData->meshs[ i ].material[ k ].m_texture != 0 )
			{
				Util::safeDelete ( meshData->meshs[ i ].material[ k ].m_texture );
			}
			meshData->meshs[ i ].material[ k ].m_texture = inTexture;
		}
	}
	return true;
}

bool CwnBaseMesh::SetAttachingTexture ( Graphic::ShaderResource* inTexture, int numMesh, int numMat )
{
	if ( !meshData ) 
		return false;
	if ( ( unsigned )numMesh >= meshData->numMesh ) 
		return false;
	if ( (unsigned)numMat >= meshData->meshs[ numMesh ].numMaterial ) 
		return false;

	if ( meshData->meshs[ numMesh ].material[ numMat ].m_texture != 0 )
	{
		Util::safeDelete ( meshData->meshs[ numMesh ].material[ numMat ].m_texture );
	}
	meshData->meshs[ numMesh ].material[ numMat ].m_texture = inTexture;
	return true;
}