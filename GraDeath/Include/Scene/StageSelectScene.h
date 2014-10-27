#ifndef _STAGE_SELECT_SCENE_H__
#define _STAGE_SELECT_SCENE_H__

#include "Scene.h"

class StageSelectScene : public Scene{
public:
	StageSelectScene();

	SCENE_STATUS Execute();
	void Draw();

private:
};


#endif	// end of StageSelectScene