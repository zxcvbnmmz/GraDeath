#ifndef _CHARACTER_SELECT_SCENE_H__
#define _CHARACTER_SELECT_SCENE_H__

#include "Scene.h"
#include <memory>

class SelectIcon;
class CharacterIcon;
class SelectCursor;

class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	std::shared_ptr< SelectIcon >		selectIcon;
	std::shared_ptr< SelectCursor >		selectCursor;
};

#endif	// end of CharacterSelectScene