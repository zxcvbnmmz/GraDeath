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
		D3DXVECTOR4 lightDir;
		D3DXVECTOR4 eye;
	}gameData;

	struct BufferData
	{
		D3DXMATRIX world;
		D3DXMATRIX wvp;
		D3DXVECTOR4 ambient;
		D3DXVECTOR4 diffuse;
		D3DXVECTOR4 specular;
		BufferData (){
			for ( int i = 0; i<4; ++i ){
				ambient[ i ] = 1;
				diffuse[ i ] = 1;
				specular[ i ] = 0;
			}
			D3DXMatrixIdentity ( &world );
			D3DXMatrixIdentity ( &wvp );
		}
	}bufferData;

};

// ************************************************************
// class	ModelStaticShader
// brief	���f���̐ÓI�V�F�[�_
// ************************************************************
class ModelStaticShader : public Shader
{
private:
	ConstantBuffer buffer[ 2 ];

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


#endif