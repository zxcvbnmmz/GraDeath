#ifndef _CHARACTER_SELECT_SCENE_H__
#define _CHARACTER_SELECT_SCENE_H__

#include "Scene.h"
#include <memory>

class SelectIcon;
class CharacterIcon;

class CharacterSelectScene : public Scene{
public:
	CharacterSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	std::shared_ptr< SelectIcon >		selectIcon;
	//std::shared_ptr< CharacterIcon >	characterIcon;
};

#endif	// end of CharacterSelectScene