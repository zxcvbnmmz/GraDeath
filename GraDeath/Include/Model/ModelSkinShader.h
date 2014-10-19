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

	struct BoneDate
	{
		D3DXMATRIX bone[ 255 ];
		BoneDate ()
		{
			for ( auto& boneInit : bone )
				D3DXMatrixIdentity ( &boneInit );
		}
	}boneData;
};

// ************************************************************
// class	ModelStaticShader
// brief	���f���̐ÓI�V�F�[�_
// ************************************************************
class ModelSkinShader : public Shader
{
private:
	ConstantBuffer buffer[ 3 ];

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


#endif