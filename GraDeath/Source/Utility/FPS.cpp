// インクルード ***********************************************
#include "Utility/FPS.h"

// コンストラクタ
FPS::FPS() :
timeStart(0), timeEnd(0), timeSum(0), Counter(0), lockFPS(60), aveFPS(60)
{
}

// デストラクタ
FPS::~FPS()
{
}

// フレームのウェイト
void FPS::WaitFrame()
{
	if (lockFPS <= Counter)
	{
		aveFPS = 1000.0f / (static_cast< float >(timeSum) / lockFPS);
		timeSum = 0;
		Counter = 0;
	}

	Counter++;

	timeEnd = timeGetTime();

	int waitTime = 1000 / static_cast< int >(lockFPS)-static_cast< int >(timeEnd - timeStart);

	bool waitFlg = (0 < waitTime);

	if (waitFlg) Sleep(waitTime);

	timeSum += timeGetTime() - timeStart;
	timeStart = timeGetTime();

}

// FPSの設定
void FPS::SetFPS(float set)
{
	lockFPS = set;
	aveFPS = set;
}

// FPSの取得
float FPS::GetFPS()
{
	return aveFPS;
}