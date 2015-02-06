// 多重インクルード防止 ***************************************
#ifndef	_FPS_H_
#define	_FPS_H_

// インクルード ***********************************************
#include <windows.h>
#include <mmsystem.h>


// ************************************************************
// class	FPSの制御
// brief	フレームレートの調整
// ************************************************************
class FPS{
private:
	DWORD	timeStart, timeEnd, timeSum;	// 開始、終了、平均
	float	lockFPS;						// 固定しているFPS
	float	aveFPS;							// 平均と取るためのFPS
	int		Counter;						// カウンタ

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	FPS();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~FPS();

	// ************************************************************
	// フレームのウェイト
	// ************************************************************
	void WaitFrame();

	// ************************************************************
	// FPSの設定
	// ************************************************************
	void SetFPS(float set);

	// ************************************************************
	// FPSの取得
	// ************************************************************
	float GetFPS();
};

#endif