// ************************************************************
// fliename	CwnStaticMesh.h
// brief	独自フォーマット静的メッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Model/ModelStaticShader.h"
#include "Graphic/Sampler/Sampler.h"

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
	buffer.Create ( sizeof( ModelStaticDatas::Data ) );
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

	ModelStaticDatas* datas;
	if ( buffer.Map ( ( void** )&datas ) )
	{
		D3DXMatrixTranspose ( &datas->world, &tData->world );
		D3DXMatrixTranspose ( &datas->wvp, &tData->wvp );

		datas->ambient = tData->ambient;
		datas->diffuse = tData->diffuse;
		datas->specular = tData->specular;
		datas->light = tData->light;
		
		buffer.Unmap ();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout ();

	// コンスタントバッファ渡す
	buffer.SetToShader ( 0 );

	// サンプラー渡す
	//Sampler::SetPointWrap ();
}