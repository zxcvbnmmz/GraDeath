// ************************************************************
// fliename	ModelSkinShader.h
// brief	モデルの静的シェーダ
// name		川口　裕
// note
// 2014.10.19
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_MODEDL_SKIN_SHADER_H_
#define	_MODEDL_SKIN_SHADER_H_

// インクルード ***********************************************
#include "Shader/Shader.h"
#include <memory>
#include "Graphic/Buffer/ConstantBuffer.h"


// ************************************************************
// struct	ModelSkinDatas
// brief	モデルの静的シェーダに使用するコンスタントバッファ
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
// brief	モデルの静的シェーダ
// ************************************************************
class ModelSkinShader : public Shader
{
private:
	ConstantBuffer buffer[ 3 ];

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	ModelSkinShader ();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~ModelSkinShader ();

	// ************************************************************
	// コンパイル
	// ************************************************************
	HRESULT Compile ();

	// ************************************************************
	// パラメータのセット
	// ************************************************************
	void SetParameters ( ConstantDataBase* );

};


#endif