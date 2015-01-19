#ifndef _STAGE_CALL_H__
#define _STAGE_CALL_H__

#include "Sound/SE/SE.h"
#include "D2D/Sprite/Sprite.h"

class StageCall{
	friend class GameScene;

	void Initialize(bool pIsEndCall);
	void Release();

	enum {
		CALLING,
		FINISHED,
	};

	StageCall();
	~StageCall(){}

	int Update();
	void Draw();

	SE startSE;
	SE endSE;

	Sprite startText;
	Sprite endText;

	D3DXVECTOR2 text_pos, text_move;

	int cTimer;

	bool callFlg;
	bool isEndCall;
};

#endif	// end of StageCall