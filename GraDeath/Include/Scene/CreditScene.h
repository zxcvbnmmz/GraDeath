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
		PAGE4,
		PAGE5,
		PAGE6,
		PAGE7,
		FADE_OUT,
		// êèéûí«â¡ÇµÇƒÇ‡ëÂè‰ïv
	}currentState;

	int ExecutePage1();
	int ExecutePage2();
	int ExecutePage3();
	int ExecutePage4();
	int ExecutePage5();
	int ExecutePage6();
	int ExecutePage7();
	int ExecuteFadeOut();
	void DrawPage1();
	void DrawPage2();
	void DrawPage3();
	void DrawPage4();
	void DrawPage5();
	void DrawPage6();
	void DrawPage7();
	void DrawFadeOut();

	Sprite sPage1, sPage2, sPage3, sPage4, sPage5, sPage6, sPage7, sBG;
	D3DXVECTOR2 sPos1, sPos2, sPos3, sPos4, sPos5, sPos6, sPos7, mPos;
	SE cancelSE, moveSE;
	FLOAT pCenter, pSide;
	std::shared_ptr<Fade> fade;
};


#endif	// end of CreditScene