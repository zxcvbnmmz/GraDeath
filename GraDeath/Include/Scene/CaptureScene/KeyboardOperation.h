// ************************************************************
// filename	KeyboardOperation.h
// brief	�L�[�{�[�h����
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef _KEYBOARDOPERATION_H_
#define _KEYBOARDOPERATION_H_

#include "Input/Keyboard.h"

// ************************************************************
// class	KeyboardOperation
// brief	�L�[�{�[�h����
// ************************************************************
class KeyboardOperation{
private:
	int selectUDNum;
	int selectUDMax;

	int selectLRNum;
	int selectLRMax;

public:
	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	KeyboardOperation();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~KeyboardOperation();

	// ************************************************************
	// �X�V
	// ************************************************************
	int Update();

	// ************************************************************
	// ���Z�b�g
	// ************************************************************
	void StateReset();

	// ************************************************************
	// �A���[�L�[�̐ݒ�
	// ************************************************************
	void SetALLARROW(int udmax, int lrmax);
	void SetALLARROW(int max);

	// ************************************************************
	// �㉺�̐ݒ�
	// ************************************************************
	void SetUpDownMax(int max);

	// ************************************************************
	// ���E�̐ݒ�
	// ************************************************************
	void SetLeftRightMax(int max);

	// ************************************************************
	// �㉺�̎擾
	// ************************************************************
	int GetUpDown();

	// ************************************************************
	// ���E�̎擾
	// ************************************************************
	int GetLeftRight();

	// ************************************************************
	// �L�[�̏�Ԃ��擾
	// ************************************************************
	bool GetKeyState(KEY_CODE key, INPUT_STATE state);
};

// �A���[�L�[�̐ݒ�
inline void KeyboardOperation::SetALLARROW(int udmax, int lrmax)
{
	selectUDMax = udmax;
	selectLRMax = lrmax;
}

inline void KeyboardOperation::SetALLARROW(int max)
{
	selectUDMax = max;
	selectLRMax = max;
}

// �㉺�̐ݒ�
inline void KeyboardOperation::SetUpDownMax(int max)
{
	selectUDMax = max;
}

// ���E�̐ݒ�
inline void KeyboardOperation::SetLeftRightMax(int max)
{
	selectLRMax = max;
}

// �㉺�̎擾
inline int KeyboardOperation::GetUpDown()
{
	return selectUDNum;
}

// ���E�̎擾
inline int KeyboardOperation::GetLeftRight()
{
	return selectLRNum;
}

#endif