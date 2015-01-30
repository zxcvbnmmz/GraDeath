// ************************************************************
// fliename	CwnSkinMesh.h
// brief	�Ǝ��t�H�[�}�b�g�ÓI���b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Graphic/Sampler/Sampler.h"
#include "Model/ModelSkinShader.h"

#include "../Resource/FbxSkinMeshShadervso.h"
#include "../Resource/FbxSkinMeshShaderpso.h"

ModelSkinShader modelSkinShader;

// �R���X�g���N�^
ModelSkinShader::ModelSkinShader (){}

// �f�X�g���N�^
ModelSkinShader::~ModelSkinShader (){}

// �R���p�C��
HRESULT ModelSkinShader::Compile ()
{
	buffer.Create ( sizeof( ModelSkinDatas::GameData ) );

	// �V�F�[�_�[�p�v���O�����錾�̒ǉ�
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

// �p�����[�^�̃Z�b�g
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

	// ���C�A�E�g�Ƃ��T���v���Ƃ��n��
	SetShaderLayout ();

	// �R���X�^���g�o�b�t�@�n��
	buffer.SetToShader ( 0 );

	// �T���v���[�n��
	Sampler::SetPointWrap ();
}