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


// コンストラクタ
ModelStaticShader::ModelStaticShader (){}

// デストラクタ
ModelStaticShader::~ModelStaticShader (){}

// コンパイル
HRESULT ModelStaticShader::Compile ()
{
	buffer[ 1 ].Create ( sizeof( ModelStaticDatas::BufferData ) );
	buffer[ 0 ].Create ( sizeof( ModelStaticDatas::GameData ) );

	D3D10_INPUT_ELEMENT_DESC layout[ ] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layout ) / sizeof( layout[ 0 ] );

	SHADER_STATUS status;
	CreateFromPrecompiledShader ( status );

	return S_OK;
}

// パラメータのセット
void ModelStaticShader::SetParameters ( ConstantDataBase* _data )
{
	void* temp = _data;
	ModelStaticDatas* tData = static_cast< ModelStaticDatas* >( _data );

	ModelStaticDatas::GameData* gameData;
	if ( buffer[ 0 ].Map ( ( void** )&gameData ) )
	{
		gameData->eye = tData->gameData.eye;
		gameData->lightDir = tData->gameData.lightDir;
		buffer[ 0 ].Unmap ();
	}

	ModelStaticDatas::BufferData* bufferData;
	if ( buffer[ 1 ].Map ( ( void** )&bufferData ) )
	{
		bufferData->ambient = tData->bufferData.ambient;
		bufferData->diffuse = tData->bufferData.diffuse;
		bufferData->specular = tData->bufferData.specular;
		bufferData->world = tData->bufferData.world;
		bufferData->wvp = tData->bufferData.wvp;

		buffer[ 1 ].Unmap ();
	}

	// レイアウトとかサンプラとか渡す
	SetShaderLayout ();

	// コンスタントバッファ渡す
	for ( int i = 0; i < 2; ++i )
	{
		buffer[ i ].SetToShader ( i );
	}

	// サンプラー渡す
	Sampler::SetPointWrap ();
}