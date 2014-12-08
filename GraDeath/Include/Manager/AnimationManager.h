#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

#include <D2D1.h>
#include "Object/ObjectParameter.h"

enum PLAYER_ACTION : unsigned int {
	ACTION_IDLE,
	ACTION_ATTACK,
	ACTION_WALK,
	ACTION_RUN,
	ACTION_DAMAGE,
	ACTION_JUMP,
	ACTION_NOTHING,
	ACTION_MAX
};

enum CURRENT_ANIMATION_STATE{
	PROCESSED,
	FINISHED,
};

class AnimationManager{
public:
	AnimationManager(){}
	virtual ~AnimationManager(){}

	bool Create(unsigned int playerNum, class Player* _player);
	void ChangeAction(PLAYER_ACTION _action, bool _loop);
	CURRENT_ANIMATION_STATE Update();
	void GetDrawingRect(D2D1_RECT_F& rect);
	const D3DXVECTOR2& GetCellSize();

	void Enable(bool flag){
		isEnable = flag;
	}

private:
	void AttachFixtureToPlayer();

	std::vector<std::shared_ptr<CellData>>::iterator currentCell;
	PLAYER_ACTION currentAction;
	unsigned int currentFrame;
	AnimationData animation;
	bool isEnable;
	bool loop;

	class Player* player;
};

#endif	// end of AnimationManager