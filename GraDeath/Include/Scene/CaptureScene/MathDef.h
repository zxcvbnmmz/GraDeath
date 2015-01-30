// ************************************************************
// filename	MathDef.h
// brief	���w�֘A
// name		����@�T
// memo
// 2013.10.24
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_MATH_DEF_H_
#define	_MATH_DEF_H_

#include <D3DX10.h>


// �f�[�^�^�錾 ***********************************************
namespace MathDef
{

	// �~����
	const static double	PI = 3.1415926535897932384626433832795;
	const static float	PI_F = 3.1415926535897932384626433832795f;

	// �~���� * 2
	const static double TWO_PI = PI * 2.0;
	const static float	TWO_PI_F = PI_F * 2.0f;

	// ************************************************************
	// ���W�A���擾
	// input : degree	- �ʓx
	// rerurn : float	- ���W�A��
	// ************************************************************
	extern float ToRadian(float degree);

	// ************************************************************
	// �ʓx�擾
	// input : radian	- ���W�A��
	// rerurn : float	- �ʓx
	// ************************************************************
	extern float ToDegree(float radian);

	// ************************************************************
	// ���[���h�s��̌v�Z
	// output : Matrix	- ���[���h�s��
	// input : Vector3	- �|�W�V����
	// input : Vector3	- �X�P�[��
	// input : Vector3	- ��]
	// Vector3 : float	- ���[���h�s��
	// ************************************************************
	extern const D3DXMATRIX& CalculationWorld(D3DXMATRIX* outWorld, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inScale);

}

#endif