// ************************************************************
// filename	KeyboardOperation.cpp
// brief	KeyboardOperation
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/KeyboardOperation.h"

// コンストラクタ
KeyboardOperation::KeyboardOperation()
{
	StateReset();
}

// デストラクタ
KeyboardOperation::~KeyboardOperation()
{
}

// 更新
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

// リセット
void KeyboardOperation::StateReset()
{
	selectUDNum = 0;
	selectLRNum = 0;
	selectUDMax = 1;	// エラー回避
	selectLRMax = 1;	// エラー回避
}

// キーの状態を取得
bool KeyboardOperation::GetKeyState(KEY_CODE key, INPUT_STATE state)
{
	if (Keyboard::CheckKey(key) == state)
		return true;
	return false;
}