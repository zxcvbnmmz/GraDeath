#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "Scene.h"

class GameScene : public Scene{
public:
	GameScene();

	SCENE_STATUS Execute();
	void Draw();

private:
};


#endif	// end of GameScene