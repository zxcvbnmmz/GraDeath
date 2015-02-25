#ifndef _STAGE_SELECT_SCENE_H__
#define _STAGE_SELECT_SCENE_H__

#include "Scene.h"
#include "Utility/FrameTimer.h"
#include <memory>

class StageIcon;
class Sprite;
class Fade;

class StageSelectScene : public Scene{
public:
	StageSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	int ExecuteMain ();
	int ExecuteOut ();

	void DrawMain ();
	void DrawOut ();

	enum CURRENT_SELECT_STATE{
		SELECT_MAIN,
		SELECT_OUT
	};

	CURRENT_SELECT_STATE currentState;

	std::shared_ptr< StageIcon > stageIcon;
	std::shared_ptr< Sprite > bgSprite;
	std::shared_ptr< Sprite > loadSprite;

	std::shared_ptr< Fade > fade;
	FrameTimer timer;

};


#endif	// end of StageSelectScene