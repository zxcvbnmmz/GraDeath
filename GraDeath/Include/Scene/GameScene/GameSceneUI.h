#ifndef _GAME_SCENE_UI_H__
#define _GAME_SCENE_UI_H__

#include "Pool/Ref.h"
#include "D2D/Sprite/Sprite.h"

class GameSceneUI : public Ref{
public:
	void Draw();

	static GameSceneUI* Create();
	static void Release();

private:
	GameSceneUI();
	GameSceneUI(const GameSceneUI&);
	GameSceneUI& operator=(const GameSceneUI&);
	~GameSceneUI();

	static GameSceneUI* ui;

	enum{
		FRAME,
		IDENTIFIER,
		UI_MAX
	};
	float posX, posY;

	static const int PLAYER_MAX = 4;
	class Sprite ground;
	class Sprite hpBar;
	class Sprite sprites[PLAYER_MAX][UI_MAX];
};

#endif	// end of GameSceneUI