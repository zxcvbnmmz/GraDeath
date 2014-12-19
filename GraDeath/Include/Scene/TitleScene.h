#ifndef _TITLE_SCENE_H__
#define _TITLE_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"
#include "Direction/Fade.h"
#include "Utility/FrameTimer.h"

class TitleScene : public Scene{
public:
	TitleScene();
	~TitleScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	Sprite sprite, sStart, sCredit, sExit, sVector;
	D3DXVECTOR2 start_pos, credit_pos, exit_pos, vect_pos,
		vect_move, start_move, credit_move, exit_move;
	int tCount, select_i;

	enum CURRENT_GAME_STATE{
		SELECT,
		FADE_OUT
	}currentState;
	int ExecuteSelect();
	int ExecuteFadeOut();

	void DrawSelect();
	void DrawFadeOut();

	void Move();
	Fade fade;
	FrameTimer timer;
};

#endif	// end of TitleScene