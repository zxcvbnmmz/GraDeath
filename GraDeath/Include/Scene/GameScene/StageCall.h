#ifndef _STAGE_CALL_H__
#define _STAGE_CALL_H__

#include "Sound/SE/SE.h"
#include "D2D/Sprite/Sprite.h"

class StageCall{
	friend class GameScene;

	void Initialize();
	void Release();

	enum {
		CALLING,
		FINISHED,
	};

	StageCall();
	~StageCall(){}

	int Update();
	void Draw();

	SE se;

	Sprite sCallText;

	D3DXVECTOR2 text_pos, text_move;

	int cTimer;

	bool callFlg;
};

#endif	// end of StageCall