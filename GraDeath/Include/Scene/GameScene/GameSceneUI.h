#ifndef _GAME_SCENE_UI_H__
#define _GAME_SCENE_UI_H__

#include "Pool/Ref.h"
#include "D2D/Sprite/Sprite.h"
#include "Object/SkillDefine.h"

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

	void DrawSkillUI ( int _num, D3DXVECTOR2& _pos );

	static GameSceneUI* ui;

	enum{
		FRAME,
		IDENTIFIER,
		UI_MAX
	};
	float posX, posY;

	enum
	{
		HP_BAR = 0,
		DEADLY_GAGE = 1,
		BAR_MAX,
	};

	static const int PLAYER_MAX = 4;
	class Sprite ground;
	class Sprite gageUI[ BAR_MAX ];
	class Sprite sprites[PLAYER_MAX][UI_MAX];
	class Sprite skillIcon[ SKILL_ID::SKILL_MAX ];
	class Sprite skillMask;
	//class Sprite skillIcon[ PLAYER_MAX ][ SKILL_ID::SKILL_MAX ];
};

#endif	// end of GameSceneUI