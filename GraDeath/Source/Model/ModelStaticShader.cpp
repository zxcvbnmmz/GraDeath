// ************************************************************
// fliename	CwnStaticMesh.h
// brief	�Ǝ��t�H�[�}�b�g�ÓI���b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Model/ModelStaticShader.h"
#include "Graphic/Sampler/Sampler.h"

#include "../Resource/FbxStaticShaderpso.h"
#include "../Resource/FbxStaticShadervso.h"

ModelStaticShader modelStaticShader;

// �R���X�g���N�^
ModelStaticShader::ModelStaticShader (){}

// �f�X�g���N�^
ModelStaticShader::~ModelStaticShader (){}

// �R���p�C��
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

// �p�����[�^�̃Z�b�g
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

	// ���C�A�E�g�Ƃ��T���v���Ƃ��n��
	SetShaderLayout ();

	// �R���X�^���g�o�b�t�@�n��
	buffer.SetToShader ( 0 );

	// �T���v���[�n��
	//Sampler::SetPointWrap ();
}