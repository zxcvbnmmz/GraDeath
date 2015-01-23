#ifndef _CREDIT_SCENE_H__
#define _CREDIT_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"
#include "Direction/Fade.h"
#include "Utility/FrameTimer.h"

class CreditScene : public Scene{
public:
	CreditScene();
	~CreditScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	enum CURRENT_CREDIT_STATE{
		NORMAL,
		FADE_OUT,
		// êèéûí«â¡ÇµÇƒÇ‡ëÂè‰ïv
	}currentState;

};


#endif	// end of CreditScene