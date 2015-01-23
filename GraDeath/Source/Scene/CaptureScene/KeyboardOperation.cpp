// ************************************************************
// filename	KeyboardOperation.cpp
// brief	KeyboardOperation
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/KeyboardOperation.h"

// �R���X�g���N�^
KeyboardOperation::KeyboardOperation()
{
	StateReset();
}

// �f�X�g���N�^
KeyboardOperation::~KeyboardOperation()
{
}

// �X�V
int KeyboardOperation::Update()
{
	if (Keyboard::CheckKey(KC_UP) == INPUT_PUSH)
		selectUDNum = (selectUDNum + selectUDMax - 1) % selectUDMax;
	if (Keyboard::CheckKey(KC_DOWN) == INPUT_PUSH)
		selectUDNum = (selectUDNum + 1) % selectUDMax;

	if (Keyboard::CheckKey(KC_RIGHT) == INPUT_PUSH)
		selectLRNum = (selectLRNum + selectLRMax - 1) % selectLRMax;
	if (Keyboard::CheckKey(KC_LEFT) == INPUT_PUSH)
		selectLRNum = (selectLRNum + 1) % selectLRMax;

	return 1;
}

// ���Z�b�g
void KeyboardOperation::StateReset()
{
	selectUDNum = 0;
	selectLRNum = 0;
	selectUDMax = 1;	// �G���[���
	selectLRMax = 1;	// �G���[���
}

// �L�[�̏�Ԃ��擾
bool KeyboardOperation::GetKeyState(KEY_CODE key, INPUT_STATE state)
{
	if (Keyboard::CheckKey(key) == state)
		return true;
	return false;
}