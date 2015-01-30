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
	int ExecuteEndCall();

	void DrawFadeIn();
	void DrawStageCall();
	void DrawButtle();
	void DrawEndCall();

	StageCall stageCall;

	enum CURRENT_GAME_STATE{
		FADE_IN,
		STAGE_CALL,
		BUTTLE,
		END_CALL,
	};
	CURRENT_GAME_STATE currentState;

	DefaultDebugDrawer drawer;

	int stageTimer;
};


#endif	// end of GameScene