#ifndef _STAGE_SELECT_SCENE_H__
#define _STAGE_SELECT_SCENE_H__

#include "Scene.h"
#include <memory>

class StageIcon;
class Sprite;

class StageSelectScene : public Scene{
public:
	StageSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	std::shared_ptr< StageIcon > stageIcon;
	std::shared_ptr< Sprite > bgSprite;

};


#endif	// end of StageSelectScene