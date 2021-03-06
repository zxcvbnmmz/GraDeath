#ifndef _RESULT_SCENE_H__
#define _RESULT_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"
#include "Sound/BGM/BGM.h"
#include "Sound/SE/SE.h"

class ResultScene : public Scene{
public:
	ResultScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	Sprite sRank[4], sChara[4], sPlayer[4], sBG;
	D3DXVECTOR2 pRank[4], pMove[4], pPlayer, pChara;
	float alpha[4];
	int timer;

	BGM bgm;
	SE vWin, winSE;
};


#endif	// end of ResulScene