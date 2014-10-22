// ************************************************************
// fliename	ModelStaticShader.h
// brief	���f���̐ÓI�V�F�[�_
// name		����@�T
// note
// 2014.10.19
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_MODEDL_STATIC_SHADER_H_
#define	_MODEDL_STATIC_SHADER_H_

// �C���N���[�h ***********************************************
#include "Shader/Shader.h"
#include <memory>
#include "Graphic/Buffer/ConstantBuffer.h"


// ************************************************************
// struct	ModelStaticDatas
// brief	���f���̐ÓI�V�F�[�_�Ɏg�p����R���X�^���g�o�b�t�@
// ************************************************************
struct ModelStaticDatas : public ConstantDataBase
{
	struct GameData
	{
		D3DXMATRIX	world;
		D3DXMATRIX	wvp;
		D3DXVECTOR4	ambient;
		D3DXVECTOR4 diffuse;
		D3DXVECTOR4 specular;
		D3DXVECTOR4 light;
	}data;	
};

// ************************************************************
// class	ModelStaticShader
// brief	���f���̐ÓI�V�F�[�_
// ************************************************************
class ModelStaticShader : public Shader
{
private:
	ConstantBuffer buffer;

public:
	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	ModelStaticShader ();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~ModelStaticShader ();

	// ************************************************************
	// �R���p�C��
	// ************************************************************
	HRESULT Compile ();

	// ************************************************************
	// �p�����[�^�̃Z�b�g
	// ************************************************************
	void SetParameters ( ConstantDataBase* );

};

extern ModelStaticShader modelStaticShader;

#endif