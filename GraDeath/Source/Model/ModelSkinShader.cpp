// ************************************************************
// fliename	CwnSkinMesh.h
// brief	独自フォーマット静的メッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Graphic/Sampler/Sampler.h"
#include "Model/ModelSkinShader.h"

#include "../Resource/FbxSkinMeshShadervso.h"
#include "../Resource/FbxSkinMeshShaderpso.h"

ModelSkinShader modelSkinShader;

// コンストラクタ
ModelSkinShader::ModelSkinShader (){}

// デストラクタ
ModelSkinShader::~ModelSkinShader (){}

// コンパイル
HRESULT ModelSkinShader::Compile ()
{
	buffer.Create ( sizeof( ModelSkinDatas::GameData ) );

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
	if ( buffer.Map ( ( void** )&gameData ) )
	{
		D3DXMatrixTranspose ( &gameData->world, &tData->data.world );
		D3DXMatrixTranspose ( &gameData->wvp, &tData->data.wvp );

		memcpy ( gameData->bone, tData->data.bone, sizeof( tData->data.bone ) );
		buffer.Unmap ();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout ();

	// コンスタントバッファ渡す
	buffer.SetToShader ( 0 );

	// サンプラー渡す
	Sampler::SetPointWrap ();
}