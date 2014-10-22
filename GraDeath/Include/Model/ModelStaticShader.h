// ************************************************************
// fliename	ModelStaticShader.h
// brief	モデルの静的シェーダ
// name		川口　裕
// note
// 2014.10.19
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_MODEDL_STATIC_SHADER_H_
#define	_MODEDL_STATIC_SHADER_H_

// インクルード ***********************************************
#include "Shader/Shader.h"
#include <memory>
#include "Graphic/Buffer/ConstantBuffer.h"


// ************************************************************
// struct	ModelStaticDatas
// brief	モデルの静的シェーダに使用するコンスタントバッファ
// ************************************************************

#pragma pack( push, 1 )
struct ModelStaticDatas : public ConstantDataBase
{
	struct Data
	{
		D3DXMATRIX	world;
		D3DXMATRIX	wvp;
		D3DXVECTOR4	ambient;
		D3DXVECTOR4 diffuse;
		D3DXVECTOR4 specular;
		D3DXVECTOR4 light;
	}data;	

	D3DXMATRIX	world;
	D3DXMATRIX	wvp;
	D3DXVECTOR4	ambient;
	D3DXVECTOR4 diffuse;
	D3DXVECTOR4 specular;
	D3DXVECTOR4 light;
};
#pragma pack( pop )

// ************************************************************
// class	ModelStaticShader
// brief	モデルの静的シェーダ
// ************************************************************
class ModelStaticShader : public Shader
{
private:
	ConstantBuffer buffer;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	ModelStaticShader ();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~ModelStaticShader ();

	// ************************************************************
	// コンパイル
	// ************************************************************
	HRESULT Compile ();

	// ************************************************************
	// パラメータのセット
	// ************************************************************
	void SetParameters ( ConstantDataBase* );

};

extern ModelStaticShader modelStaticShader;

#endif