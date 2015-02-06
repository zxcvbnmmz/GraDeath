// ************************************************************
// filename	Texture.cpp
// brief	�e�N�X�`��
// name		����@�T
// memo
// 2013.06.04
// ************************************************************

// �C���N���[�h ***********************************************
#include "Graphic/Texture/Texture.h"
#include "Graphic/Sampler/Sampler.h"
#include "Util/SafeDelete.h"
#include <d3d10_1.h>


// �R���X�g���N�^
Texture::Texture() : texture( 0 )
{
}

// �f�X�g���N�^
Texture::~Texture()
{
	Util::safeRelease( &texture );
	Util::safeRelease ( &sampleLiner );
}

// �e�N�X�`������
HRESULT Texture::CreateTexture( LPCWSTR filename )
{
	D3D10_SAMPLER_DESC SamDesc;
	ZeroMemory( &SamDesc, sizeof( D3D10_SAMPLER_DESC ) );
	SamDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
	D3DCore::RefDevice()->CreateSamplerState( &SamDesc, &sampleLiner );
	Sampler sampler;
	sampler.SetLinearWrap ();

	// �e�N�X�`���ǂݍ��݂��s��
	if ( FAILED( D3DX10CreateShaderResourceViewFromFile(
		D3DCore::RefDevice(),
		filename,
		0,//&info,
		0,
		&texture,
		0 ) ) )
	{
		return E_FAIL;
	}
	return S_OK;
}

// ���
void Texture::Release()
{
	Util::safeRelease ( &texture );
	Util::safeRelease ( &sampleLiner );
}

