// ************************************************************
// fliename	ModelSkinShader.h
// brief	���f���̐ÓI�V�F�[�_
// name		����@�T
// note
// 2014.10.19
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_MODEDL_SKIN_SHADER_H_
#define	_MODEDL_SKIN_SHADER_H_

// �C���N���[�h ***********************************************
#include "Shader/Shader.h"
#include <memory>
#include "Graphic/Buffer/ConstantBuffer.h"


// ************************************************************
// struct	ModelSkinDatas
// brief	���f���̐ÓI�V�F�[�_�Ɏg�p����R���X�^���g�o�b�t�@
// ************************************************************
struct ModelSkinDatas : public ConstantDataBase
{
	struct GameData
	{
		D3DXMATRIX	world;
		D3DXMATRIX	wvp;
		D3DXMATRIX	bone[ 255 ];
	}data;
};

// ************************************************************
// class	ModelStaticShader
// brief	���f���̐ÓI�V�F�[�_
// ************************************************************
class ModelSkinShader : public Shader
{
private:
	ConstantBuffer buffer;

public:
	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	ModelSkinShader ();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~ModelSkinShader ();

	// ************************************************************
	// �R���p�C��
	// ************************************************************
	HRESULT Compile ();

	// ************************************************************
	// �p�����[�^�̃Z�b�g
	// ************************************************************
	void SetParameters ( ConstantDataBase* );

};

extern ModelSkinDatas modelSkinDatas;

#endif