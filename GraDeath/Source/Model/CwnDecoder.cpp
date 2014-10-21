// ************************************************************
// fliename	CwnDecoder.cpp
// brief	独自フォーマット読込
// name		川口　裕
// memo
// 2013.08.21
// ************************************************************

// インクルード ***********************************************
#include "Model/CwnDecoder.h"
#include "Utility/SafeDelete.h"
#include "Model/MeshDef.h"
//#include "Shader.h"
/*
#include "ModelStaticShader.h"
#include "ModelSkinShader.h"
*/
#include <fstream>
#include <locale.h>
#include "Graphic/ShaderResource/ShaderResource.h"


// コンストラクタ
CwnDecoder::CwnDecoder()
{
	ZeroMemory( this, sizeof( CwnDecoder ) );
}

// デストラクタ
CwnDecoder::~CwnDecoder()
{
	Release();
}

// 解放
void CwnDecoder::Release()
{
	for ( DWORD num = 0; num < meshData->numMesh; num++ )
	{
		Util::safeDeleteArray ( meshData->meshs[ num ].vertexList );
		Util::safeDeleteArray ( meshData->meshs[ num ].indexList );
		Util::safeDeleteArray ( meshData->meshs[ num ].subSet );
		for ( DWORD i = 0; i < meshData->meshs[ num ].numMaterial; i++ )
		{
			Util::safeDelete ( meshData->meshs[ num ].material->m_texture );
		}
		Util::safeDeleteArray ( meshData->meshs[ num ].material );
	}
	Util::safeDeleteArray ( meshData->meshs );
	Util::safeDelete ( meshData );
}

// 読込
bool CwnDecoder::LoadCwn( char* filename, char* path )
{

	std::wstring	rootPathTemp;
	std::string		filePathTemp;

	filePathTemp = path;
	// ファイル名をマルチからワイドに変換
	size_t len = filePathTemp.size();
	//setlocale( LC_ALL, "japanese" );
	wchar_t tempPath[ 100 ] = { 0 };
	mbstowcs_s( &len, tempPath, filePathTemp.size() + 1, filePathTemp.c_str(), _TRUNCATE );

	rootPathTemp = tempPath;
	filePathTemp += filename;

	// キャストして渡す
	filePath = const_cast< char* >( filePathTemp.c_str() );
	rootPath = const_cast< wchar_t* >( rootPathTemp.c_str() );

	std::ifstream ifs( filePath, std::ios::binary );

	if( ifs.fail() ) return false;

	meshData = new MeshData ();

	// モデル名
	ifs.read ( ( char* )meshData->modelName, sizeof( meshData->modelName ) );

	// メッシュ数取得
	ifs.read ( ( char* )&meshData->numMesh, sizeof( DWORD ) );

	// ボーン情報取得
	ifs.read ( ( char* )&meshData->numBone, sizeof( DWORD ) );

	// メッシュの動的生成
	meshData->meshs = new CwnMesh[ meshData->numMesh ];

	for ( DWORD num = 0; num < meshData->numMesh; num++ )
	{
		// バーテクス情報取得
		ifs.read ( ( char* )&meshData->meshs[ num ].numVert, sizeof( DWORD ) );
		CwnVertex* vertex = new CwnVertex[ meshData->meshs[ num ].numVert ];
		ifs.read ( ( char* )vertex, sizeof( CwnVertex )* meshData->meshs[ num ].numVert );

		// 面情報取得
		ifs.read ( ( char* )&meshData->meshs[ num ].numFace, sizeof( DWORD ) );
		unsigned short* index = new unsigned short[ meshData->meshs[ num ].numFace ];
		ifs.read ( ( char* )index, sizeof( unsigned short )* meshData->meshs[ num ].numFace );

		// 材質情報取得
		ifs.read ( ( char* )&meshData->meshs[ num ].numMaterial, sizeof( DWORD ) );
		CwnMaterial* material = new CwnMaterial[ meshData->meshs[ num ].numMaterial ];
		ifs.read ( ( char* )material, sizeof( CwnMaterial )* meshData->meshs[ num ].numMaterial );

		// バーテクスの読込
		meshData->meshs[ num ].vertexList = new MeshVertex[ meshData->meshs[ num ].numVert ];
		LoadVertex ( meshData->meshs[ num ].vertexList, vertex, meshData->meshs[ num ].numVert );
		meshData->meshs[ num ].vertexBuffer.Create ( meshData->meshs[ num ].numVert, sizeof( MeshVertex ), meshData->meshs[ num ].vertexList );

		// インデックスの読込
		LoadIndex( index, num );

		// 材質読込
		LoadMaterial ( &meshData->meshs[ num ], material );

		Util::safeDeleteArray ( vertex );
		Util::safeDeleteArray ( index );
		Util::safeDeleteArray ( material );
	}
	return true;
}

// バーテクスの読込
void CwnDecoder::LoadVertex( MeshVertex* outVert, CwnVertex* inVert, DWORD numVert )
{
	for ( DWORD i = 0; i < numVert; i++ )
	{
		outVert[ i ].pos	= D3DXVECTOR3 ( inVert[ i ].pos[ 0 ], inVert[ i ].pos[ 1 ], inVert[ i ].pos[ 2 ] );
		outVert[ i ].normal = D3DXVECTOR3 ( inVert[ i ].normal[ 0 ], inVert[ i ].normal[ 1 ], inVert[ i ].normal[ 2 ] );
		outVert[ i ].uv		= D3DXVECTOR2 ( inVert[ i ].uv[ 0 ], inVert[ i ].uv[ 1 ] );

		for ( int j = 0; j < 4; j++ )
		{
			outVert[ i ].boneIndex[ j ] = inVert[ i ].matrixIndex[ j ];
			outVert[ i ].boneWeight[ j ] = inVert[ i ].weight[ j ];
		}
	}
}

// インデックスの読込
void CwnDecoder::LoadIndex( unsigned short* inIndex, int inNum )
{
	DWORD faceNum = meshData->meshs[ inNum ].numFace;
	meshData->meshs[ inNum ].indexList = new int[ faceNum ];
	for ( DWORD i = 0; i < faceNum; i++ )
	{
		meshData->meshs[ inNum ].indexList[ i ]  = static_cast< int >( inIndex[ i ] );
	}
	meshData->meshs[ inNum ].indexBuffer.Create( faceNum, sizeof( int ), meshData->meshs[ inNum ].indexList );
}

// 材質の読込
void CwnDecoder::LoadMaterial( CwnMesh* outMesh, CwnMaterial* inMateriall )
{
	UINT materialEnd	= 0;
	outMesh->material	= new MeshMaterial[ outMesh->numMaterial ];
	outMesh->subSet		= new MeshSubSet[ outMesh->numMaterial ];
	outMesh->numSub		= outMesh->numMaterial;

	for ( DWORD i = 0; i < outMesh->numMaterial; i++ )
	{
		CopyMaterial( outMesh->material[ i ], inMateriall[ i ] );

		MultiByteToWideChar( 
				CP_ACP, 
				MB_PRECOMPOSED, 
				inMateriall[ i ].textureFileName,
				strlen( inMateriall[ i ].textureFileName ),
				outMesh->material[ i ].textureName,
				20 );

		std::wstring temp = outMesh->material[ i ].textureName;
		temp += L".png";
		std::wstring fileName = rootPath;
		fileName += temp;
		
		if ( lstrlen( outMesh->material[ i ].textureName ) > 0)
		{
			outMesh->material[ i ].m_texture = new ShaderResource();
			outMesh->material[ i ].m_texture->Create( fileName.c_str() );
		}

		// サブセットの設定
		outMesh->subSet[ i ].faceStart	= materialEnd;
		outMesh->subSet[ i ].faceCount	= inMateriall[ i ].numFace;
		outMesh->subSet[ i ].matIndex	= i;

		materialEnd += inMateriall[ i ].numFace;
	}
}

// マテリアルのコピー
void CwnDecoder::CopyMaterial( MeshMaterial& outMaterial, CwnMaterial& inMaterial )
{
	outMaterial.ambient.x = inMaterial.ambient[ 0 ];
	outMaterial.ambient.y = inMaterial.ambient[ 1 ];
	outMaterial.ambient.z = inMaterial.ambient[ 2 ];
	outMaterial.ambient.w = inMaterial.alpha;

	outMaterial.diffuse.x = inMaterial.diffuse[ 0 ];
	outMaterial.diffuse.y = inMaterial.diffuse[ 1 ];
	outMaterial.diffuse.z = inMaterial.diffuse[ 2 ];
	outMaterial.diffuse.w = inMaterial.alpha;

	outMaterial.specular.x = inMaterial.specular[ 0 ];
	outMaterial.specular.y = inMaterial.specular[ 1 ];
	outMaterial.specular.z = inMaterial.specular[ 2 ];
	outMaterial.specular.w = inMaterial.alpha;

	outMaterial.power = inMaterial.power;
}

// テクスチャのアタッチ
bool CwnDecoder::SetAttachingTexture( const MeshTextures* textures )
{
	if ( meshData->numMesh != textures->numMesh )
		return false;

	for ( DWORD i = 0; i < meshData->numMesh; i++ )
	{
		if ( meshData->meshs[ i ].numMaterial != textures->texData[ i ].numMat )
			return false;

		for ( DWORD k = 0; k < meshData->meshs[ i ].numMaterial; k++ )
		{
			meshData->meshs[ i ].material[ k ].m_texture = textures->texData[ i ].texture;
		}
	}
	return true;
}
