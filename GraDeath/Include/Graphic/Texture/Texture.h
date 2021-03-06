// ************************************************************
// filename	D3DTexture.h
// brief	テクスチャ
// name		川口　裕
// memo
// 2013.06.04
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_TEXTURE_H_
#define	_TEXTURE_H_

// インクルード ***********************************************
struct D3DX10_IMAGE_LOAD_INFO;
struct ID3D10ShaderResourceView;
struct ID3D10SamplerState;


// ************************************************************
// class	Texture
// brief	テクスチャ
// ************************************************************
class Texture{
private:
	D3DX10_IMAGE_LOAD_INFO		info;

	ID3D10ShaderResourceView*	texture;
	ID3D10SamplerState*			sampleLiner;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	Texture();
	
	// ************************************************************
	// デストラクタ
	// ************************************************************
	~Texture();

	// ************************************************************
	// テクスチャ生成
	// ************************************************************
	HRESULT CreateTexture( LPCWSTR filename );

	// ************************************************************
	// 解放
	// ************************************************************
	void Release();

	// ************************************************************
	// テクスチャ取得
	// ************************************************************
	ID3D10ShaderResourceView** RefTexture();

	// ************************************************************
	// サンプラーステートの取得
	// ************************************************************
	ID3D10SamplerState** RefSampler();

};

// テクスチャ取得
inline ID3D10ShaderResourceView** Texture::RefTexture()
{
	return &texture;
}

// サンプラーステートの取得
inline ID3D10SamplerState** Texture::RefSampler()
{
	return &sampleLiner;
}

#endif