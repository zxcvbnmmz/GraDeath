// ************************************************************
// filename	GamePad.h
// brief	XInputの関数を纏めたラッパー
// name		川口　裕
// note
// 2014.10.10
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _GAME_PAD_H_
#define _GAME_PAD_H_

#include "InputState.h"

// ボタンのステート
enum BUTTON_ID
{
	BUTTON_UP = 0x0001,
	BUTTON_DOWN = 0x0002,
	BUTTON_LEFT = 0x0004,
	BUTTON_RIGTH = 0x0008,
	BUTTON_START = 0x0010,
	BUTTON_BACK = 0x0020,
	BUTTON_LEFT_THUMB = 0x0040,	// Lトリガー
	BUTTON_RIGHT_THUMB = 0x0080,	// Rトリガー
	BUTTON_LEFT_SHOULDER = 0x0100,	// RBボタン
	BUTTON_RIGHT_SHOULDER = 0x0200,	// LBボタン
	BUTTON_A = 0x1000,
	BUTTON_B = 0x2000,
	BUTTON_X = 0x4000,
	BUTTON_Y = 0x8000,
};

// PADのナンバー
enum PAD_NUM
{
	PAD_1 = 0,
	PAD_2,
	PAD_3,
	PAD_4
};


// ************************************************************
// namespace	GamePad
// brief		XInputの関数を纏めたラッパー
// ************************************************************
namespace GamePad
{
	// ************************************************************
	// 初期化
	// ************************************************************
	void init ();

	// ************************************************************
	// 更新
	// ************************************************************
	int update ();

	// ************************************************************
	// 閾値の設定
	// 0.0〜1.0fの間で定義
	// ************************************************************
	void setThreshold ( float );

	// ************************************************************
	// スティックのデットゾーン設定
	// ************************************************************
	void setStickDeadZone ( bool );

	// ************************************************************
	// ゲームパッドのボタン情報取得
	// ************************************************************
	INPUT_STATE getGamePadState(PAD_NUM, BUTTON_ID, int* _count = nullptr);

	// ************************************************************
	// ゲームパッドのLRトリガー情報取得
	// ************************************************************
	int getRTriggerState ( PAD_NUM, int* _trigger = nullptr );
	int getLTriggerState ( PAD_NUM, int* _trigger = nullptr );

	// ************************************************************
	// ゲームパッドのスティック情報取得
	// ************************************************************
	bool getRStickState ( PAD_NUM, float& );
	bool getLStickState ( PAD_NUM, float& );

	// ************************************************************
	// いずれかのゲームパッドのボタン情報取得
	// ************************************************************
	bool getAnyGamePadPressed(BUTTON_ID);

	// ************************************************************
	// ゲームパッドが有効かどうかを取得する
	// ************************************************************
	bool IsActive(PAD_NUM);

	// ************************************************************
	// スティックの傾きを取得する（-32767〜32767の範囲）
	// ************************************************************
	int getLStickLean(PAD_NUM _num);
	int getRStickLean(PAD_NUM _num);
};

#endif