#ifndef _CREDIT_SCENE_H__
#define _CREDIT_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"
#include "Direction/Fade.h"
#include "Utility/FrameTimer.h"
#include "Sound/SE/SE.h"
#include "Direction/Fade.h"

class CreditScene : public Scene{
public:
	CreditScene();
	~CreditScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	enum CURRENT_CREDIT_STATE{
		PAGE1,
		PAGE2,
		PAGE3,
		FADE_OUT,
		// 随時追加しても大丈夫
	}currentState;

	int ExecutePage1();
	int ExecutePage2();
	int ExecutePage3();
	int ExecuteFadeOut();
	void DrawPage1();
	void DrawPage2();
	void DrawPage3();
	void DrawFadeOut();

	Sprite sPage1, sPage2, sPage3;
	D3DXVECTOR2 sPos1, sPos2, sPos3, mPos;
	SE cancelSE, moveSE;

	std::shared_ptr<Fade> fade;
};


#endif	// end of CreditScene