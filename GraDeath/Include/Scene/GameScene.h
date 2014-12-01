#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "Scene.h"

class GameScene : public Scene{
public:
	GameScene();

	~GameScene ();

	SCENE_STATUS Execute();
	void Draw();

	int ExecuteSample();
	void DrawSample();
	void DrawSample2();

private:
};


#endif	// end of GameScene