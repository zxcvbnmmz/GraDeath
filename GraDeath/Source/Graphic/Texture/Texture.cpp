// ************************************************************
// filename	Texture.cpp
// brief	テクスチャ
// name		川口　裕
// memo
// 2013.06.04
// ************************************************************

// インクルード ***********************************************
#include "Graphic/Texture/Texture.h"
#include "Graphic/Sampler/Sampler.h"
#include "Util/SafeDelete.h"
#include <d3d10_1.h>


// コンストラクタ
Texture::Texture() : texture( 0 )
{
}

// デストラクタ
Texture::~Texture()
{
	Util::safeRelease( &texture );
	Util::safeRelease ( &sampleLiner );
}

// テクスチャ生成
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

	// テクスチャ読み込みを行う
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

// 解放
void Texture::Release()
{
	Util::safeRelease ( &texture );
	Util::safeRelease ( &sampleLiner );
}

