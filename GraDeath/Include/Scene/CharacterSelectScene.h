#ifndef _CHARACTER_SELECT_SCENE_H__
#define _CHARACTER_SELECT_SCENE_H__

#include "Scene.h"
#include <memory>
#include "Utility/FrameTimer.h"

class SelectCursor;
class Sprite;

class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene();


	SCENE_STATUS Execute();
	void Draw();

private:
	std::shared_ptr< SelectCursor >		selectCursor;
	int ExecutePreDecide();
	int ExecuteFadeOut();

	std::shared_ptr< Sprite > bgSprite;
	FrameTimer timer;
	bool countFlg;
};

#endif	// end of CharacterSelectScene