#ifndef _CHARACTER_SELECT_SCENE_H__
#define _CHARACTER_SELECT_SCENE_H__

#include "Scene.h"
#include <memory>

class SelectCursor;

class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene();


	SCENE_STATUS Execute();
	void Draw();

private:
	std::shared_ptr< SelectCursor >		selectCursor;
	int ExecutePreDecide();
	int ExecuteFadeOut();
};

#endif	// end of CharacterSelectScene