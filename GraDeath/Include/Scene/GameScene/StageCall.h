#ifndef _STAGE_CALL_H__
#define _STAGE_CALL_H__

#include "Sound/SE/SE.h"

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
};

#endif	// end of StageCall