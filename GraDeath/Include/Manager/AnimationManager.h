#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

#include <D2D1.h>
#include "Object/ObjectParameter.h"
#include "D2D/Sprite/Sprite.h"
#include "Sound/SE/SE.h"

enum PLAYER_ACTION : unsigned int {
	ACTION_IDLE,
	ACTION_WALK,
	ACTION_JUMP_RISE,
	ACTION_JUMP_FALL,
	ACTION_JUMP_LAND,
	ACTION_SKILL,
	ACTION_SKILL_2,
	ACTION_SKILL_3,
	ACTION_DAMAGE,
	//ACTION_SKILL,
	//ACTION_SKILL,
	ACTION_MAX
};

enum PLAYER_DIRECTION{
	RIGHT = FLIP_NONE,
	LEFT = FLIP_HORIZONTAL,
	SAME_BEFORE,
};

enum CURRENT_ANIMATION_STATE{
	PROCESSED,
	FINISHED,
};

class AnimationManager{
public:
	AnimationManager(){}
	virtual ~AnimationManager(){}

	bool Create(unsigned int playerNum, class Player* _player, float scale = 1.0f);
	void ChangeAction(PLAYER_ACTION _action, bool _loop, PLAYER_DIRECTION _dir);
	CURRENT_ANIMATION_STATE Update();
	void GetDrawingRect(D2D1_RECT_F& rect);
	const D3DXVECTOR2& GetCellSize();
	PLAYER_DIRECTION GetCurrentDirecton(){
		return dir;
	}

	void Enable(bool flag){
		isEnable = flag;
	}

private:
	void AttachFixtureToPlayer();
	void Reverse();

	std::vector<std::shared_ptr<CellData>>::iterator currentCell;
	PLAYER_ACTION currentAction;
	unsigned int currentFrame;
	AnimationData animation;
	bool isEnable;
	bool loop;
	PLAYER_DIRECTION dir;
	class Player* player;
};

#endif	// end of AnimationManager