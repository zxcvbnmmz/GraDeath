// ************************************************************
// filename	KeyboardOperation.h
// brief	キーボード操作
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _KEYBOARDOPERATION_H_
#define _KEYBOARDOPERATION_H_

#include "Input/Keyboard.h"

// ************************************************************
// class	KeyboardOperation
// brief	キーボード操作
// ************************************************************
class KeyboardOperation{
private:
	int selectUDNum;
	int selectUDMax;

	int selectLRNum;
	int selectLRMax;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	KeyboardOperation();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~KeyboardOperation();

	// ************************************************************
	// 更新
	// ************************************************************
	int Update();

	// ************************************************************
	// リセット
	// ************************************************************
	void StateReset();

	// ************************************************************
	// アローキーの設定
	// ************************************************************
	void SetALLARROW(int udmax, int lrmax);
	void SetALLARROW(int max);

	// ************************************************************
	// 上下の設定
	// ************************************************************
	void SetUpDownMax(int max);

	// ************************************************************
	// 左右の設定
	// ************************************************************
	void SetLeftRightMax(int max);

	// ************************************************************
	// 上下の取得
	// ************************************************************
	int GetUpDown();

	// ************************************************************
	// 左右の取得
	// ************************************************************
	int GetLeftRight();

	// ************************************************************
	// キーの状態を取得
	// ************************************************************
	bool GetKeyState(KEY_CODE key, INPUT_STATE state);
};

// アローキーの設定
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

// 上下の設定
inline void KeyboardOperation::SetUpDownMax(int max)
{
	selectUDMax = max;
}

// 左右の設定
inline void KeyboardOperation::SetLeftRightMax(int max)
{
	selectLRMax = max;
}

// 上下の取得
inline int KeyboardOperation::GetUpDown()
{
	return selectUDNum;
}

// 左右の取得
inline int KeyboardOperation::GetLeftRight()
{
	return selectLRNum;
}

#endif