// ************************************************************
// filename	MathDef.cpp
// brief	数学関連
// name		川口　裕
// memo
// 2013.10.24
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/MathDef.h"


// データ型宣言 ***********************************************
namespace MathDef
{

	// ラジアン取得
	float ToRadian(float degree)
	{
		return (degree)* (PI_F / 180.0f);
	}

	// 弧度取得
	float ToDegree(float radian)
	{
		return (radian)* (180.0f / PI_F);
	}

	const D3DXMATRIX& CalculationWorld(D3DXMATRIX* outWorld, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inScale)
	{
		D3DXMATRIX matWorld, matScale, matRot, matTrans;
		 
		// スケーリング、回転、移動
		D3DXMatrixScaling(&matScale, inScale.x, inScale.y, inScale.z);
		D3DXMatrixRotationYawPitchRoll(&matRot, inRot.y, inRot.x, inRot.z);
		D3DXMatrixTranslation(&matTrans, inPos.x, inPos.y, inPos.z);

		// ワールド行列に掛け合わせ
		matWorld = matScale * matRot * matTrans;

		*outWorld = matWorld;

		return *outWorld;
	}

}