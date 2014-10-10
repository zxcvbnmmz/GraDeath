#ifndef _TITLE_SCENE_H__
#define _TITLE_SCENE_H__

#include "Scene.h"

class TitleScene : public Scene{
public:
	TitleScene();

	SCENE_STATUS Execute();
	void Draw();

private:
};

#endif	// end of TitleScene