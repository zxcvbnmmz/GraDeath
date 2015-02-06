// ************************************************************
// filename	MathDef.h
// brief	数学関連
// name		川口　裕
// memo
// 2013.10.24
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_MATH_DEF_H_
#define	_MATH_DEF_H_

#include <D3DX10.h>


// データ型宣言 ***********************************************
namespace MathDef
{

	// 円周率
	const static double	PI = 3.1415926535897932384626433832795;
	const static float	PI_F = 3.1415926535897932384626433832795f;

	// 円周率 * 2
	const static double TWO_PI = PI * 2.0;
	const static float	TWO_PI_F = PI_F * 2.0f;

	// ************************************************************
	// ラジアン取得
	// input : degree	- 弧度
	// rerurn : float	- ラジアン
	// ************************************************************
	extern float ToRadian(float degree);

	// ************************************************************
	// 弧度取得
	// input : radian	- ラジアン
	// rerurn : float	- 弧度
	// ************************************************************
	extern float ToDegree(float radian);

	// ************************************************************
	// ワールド行列の計算
	// output : Matrix	- ワールド行列
	// input : Vector3	- ポジション
	// input : Vector3	- スケール
	// input : Vector3	- 回転
	// Vector3 : float	- ワールド行列
	// ************************************************************
	extern const D3DXMATRIX& CalculationWorld(D3DXMATRIX* outWorld, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inScale);

}

#endif