#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "Scene.h"
#include "World/DebugDrawer.h"
#include "Scene/GameScene/StageCall.h"

class GameScene : public Scene{
public:
	GameScene();

	~GameScene ();

	SCENE_STATUS Execute();
	void Draw();

private:
	int ExecuteFadeIn();
	int ExecuteStageCall();
	int ExecuteButtle();

	void DrawFadeIn();
	void DrawStageCall();
	void DrawButtle();

	StageCall stageCall;

	enum CURRENT_GAME_STATE{
		FADE_IN,
		STAGE_CALL,
		BUTTLE,
	};
	CURRENT_GAME_STATE currentState;

	DefaultDebugDrawer drawer;
};


#endif	// end of GameScene