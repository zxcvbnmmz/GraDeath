// ************************************************************
// filename	MathDef.cpp
// brief	���w�֘A
// name		����@�T
// memo
// 2013.10.24
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/MathDef.h"


// �f�[�^�^�錾 ***********************************************
namespace MathDef
{

	// ���W�A���擾
	float ToRadian(float degree)
	{
		return (degree)* (PI_F / 180.0f);
	}

	// �ʓx�擾
	float ToDegree(float radian)
	{
		return (radian)* (180.0f / PI_F);
	}

	const D3DXMATRIX& CalculationWorld(D3DXMATRIX* outWorld, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inScale)
	{
		D3DXMATRIX matWorld, matScale, matRot, matTrans;
		 
		// �X�P�[�����O�A��]�A�ړ�
		D3DXMatrixScaling(&matScale, inScale.x, inScale.y, inScale.z);
		D3DXMatrixRotationYawPitchRoll(&matRot, inRot.y, inRot.x, inRot.z);
		D3DXMatrixTranslation(&matTrans, inPos.x, inPos.y, inPos.z);

		// ���[���h�s��Ɋ|�����킹
		matWorld = matScale * matRot * matTrans;

		*outWorld = matWorld;

		return *outWorld;
	}

}