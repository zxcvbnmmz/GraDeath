// ************************************************************
// fliename	CwnSkinMesh.h
// brief	独自フォーマット静的メッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Model/ModelSkinShader.h"
#include "Graphic/Sampler/Sampler.h"

#include "../Resource/FbxSkinMeshShadervso.h"
#include "../Resource/FbxSkinMeshShaderpso.h"

// コンストラクタ
ModelSkinShader::ModelSkinShader (){}

// デストラクタ
ModelSkinShader::~ModelSkinShader (){}

// コンパイル
HRESULT ModelSkinShader::Compile ()
{
	buffer[ 2 ].Create ( sizeof( ModelSkinDatas::BoneDate ) );
	buffer[ 1 ].Create ( sizeof( ModelSkinDatas::BufferData ) );
	buffer[ 0 ].Create ( sizeof( ModelSkinDatas::GameData ) );

	// シェーダー用プログラム宣言の追加
	D3D10_INPUT_ELEMENT_DESC layout[ ] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layout ) / sizeof( layout[ 0 ] );

	SHADER_STATUS status = { g_SkinMeshVS, sizeof(g_SkinMeshVS), g_SkinMeshPS, sizeof(g_SkinMeshPS), layout, numElements };
	CreateFromPrecompiledShader(status);

	return S_OK;
}

// パラメータのセット
void ModelSkinShader::SetParameters ( ConstantDataBase* _data )
{
	void* temp = _data;
	ModelSkinDatas* tData = static_cast< ModelSkinDatas* >( _data );

	ModelSkinDatas::GameData* gameData;
	if ( buffer[ 0 ].Map ( ( void** )&gameData ) )
	{
		gameData->eye = tData->gameData.eye;
		gameData->lightDir = tData->gameData.lightDir;
		buffer[ 0 ].Unmap ();
	}

	ModelSkinDatas::BufferData* bufferData;
	if ( buffer[ 1 ].Map ( ( void** )&bufferData ) )
	{
		bufferData->ambient = tData->bufferData.ambient;
		bufferData->diffuse = tData->bufferData.diffuse;
		bufferData->specular = tData->bufferData.specular;
		bufferData->world = tData->bufferData.world;
		bufferData->wvp = tData->bufferData.wvp;

		buffer[ 1 ].Unmap ();
	}

	ModelSkinDatas::BoneDate* boneData;
	if ( buffer[ 2 ].Map ( ( void** )&boneData ) )
	{
		memcpy ( boneData->bone, tData->boneData.bone, sizeof( tData->boneData.bone ) );

		buffer[ 2 ].Unmap ();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout ();

	// コンスタントバッファ渡す
	for ( int i = 0; i < 3; ++i )
	{
		buffer[ i ].SetToShader ( i );
	}

	// サンプラー渡す
	Sampler::SetPointWrap ();
}