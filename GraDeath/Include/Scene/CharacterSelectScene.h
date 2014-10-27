#ifndef _CHARACTER_SELECT_SCENE_H__
#define _CHARACTER_SELECT_SCENE_H__

#include "Scene.h"

class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
};

#endif	// end of CharacterSelectScene