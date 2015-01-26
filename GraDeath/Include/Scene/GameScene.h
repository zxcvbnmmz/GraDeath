#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "Scene.h"
#include "World/DebugDrawer.h"
#include "Scene/GameScene/StageCall.h"
#include "Sound/BGM/BGM.h"

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
	int ExecuteSurvive();
	int ExecuteEndCall();

	void DrawFadeIn();
	void DrawStageCall();
	void DrawButtle();
	void DrawSurvive();
	void DrawEndCall();

	StageCall stageCall;

	enum CURRENT_GAME_STATE{
		FADE_IN,
		STAGE_CALL,
		BUTTLE,
		SURVIVE_ONE,
		END_CALL,
	};
	CURRENT_GAME_STATE currentState;

	DefaultDebugDrawer drawer;

	int stageTimer;

	BGM bgm;


};


#endif	// end of GameScene