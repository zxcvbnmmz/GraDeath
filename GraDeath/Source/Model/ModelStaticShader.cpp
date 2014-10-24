// ************************************************************
// fliename	CwnStaticMesh.h
// brief	独自フォーマット静的メッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Graphic/Sampler/Sampler.h"
#include "Model/ModelStaticShader.h"

#include "../Resource/FbxStaticShaderpso.h"
#include "../Resource/FbxStaticShadervso.h"

ModelStaticShader modelStaticShader;

// コンストラクタ
ModelStaticShader::ModelStaticShader (){}

// デストラクタ
ModelStaticShader::~ModelStaticShader (){}

// コンパイル
HRESULT ModelStaticShader::Compile ()
{
	buffer.Create ( sizeof( ModelStaticDatas::GameData ) );
//	buffer.Create ( 192 );

	D3D10_INPUT_ELEMENT_DESC layout[ ] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layout ) / sizeof( layout[ 0 ] );

	SHADER_STATUS status = { g_FbxStaticShaderVS, sizeof( g_FbxStaticShaderVS ), g_FbxStaticShaderPS, sizeof( g_FbxStaticShaderPS ), layout, numElements };
	CreateFromPrecompiledShader ( status );

	return S_OK;
}

// パラメータのセット
void ModelStaticShader::SetParameters ( ConstantDataBase* _data )
{
	void* temp = _data;
	ModelStaticDatas* tData = static_cast< ModelStaticDatas* >( _data );

	ModelStaticDatas::GameData* datas;
	if ( buffer.Map ( ( void** )&datas ) )
	{
		D3DXMatrixTranspose(&datas->world, &tData->data.world);
		D3DXMatrixTranspose(&datas->wvp, &tData->data.wvp);

		datas->ambient = tData->data.ambient;
		datas->diffuse = tData->data.diffuse;
		datas->specular = tData->data.specular;
		datas->light = tData->data.light;
		
		buffer.Unmap ();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout ();

	// コンスタントバッファ渡す
	buffer.SetToShader ( 0 );

	// サンプラー渡す
	//Sampler::SetPointWrap ();
}