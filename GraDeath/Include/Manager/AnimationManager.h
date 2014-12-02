#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

#include <D2D1.h>
#include "Object/ObjectParameter.h"

enum PLAYER_ACTION : unsigned int {
	ACTION_RUN,
	ACTION_WALK,
	ACTION_ATTACK,
	ACTION_IDLE,
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

	bool Create(unsigned int playerNum);
	void ChangeAction(PLAYER_ACTION _action, bool _loop);
	CURRENT_ANIMATION_STATE Update();
	void GetDrawingRect(D2D1_RECT_F& rect);

	void Enable(bool flag){
		isEnable = flag;
	}

	bool IsEnd();

private:
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;
	PLAYER_ACTION currentAction;
	unsigned int currentFrame;
	AnimationData animation;
	bool isEnable;
	bool loop;
};

#endif	// end of AnimationManager