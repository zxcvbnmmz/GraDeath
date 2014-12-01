#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

#include <D2D1.h>
#include "Object/ObjectParameter.h"


enum PLAYER_ACTION{
	ACTION_IDLE,
	ACTION_WALK,
	ACTION_RUN,
	ACTION_ATTACK,
};

enum CURRENT_STATE{
	PROCESSED,
	FINISHED,
};

class AnimationManager{
public:
	AnimationManager(){}
	virtual ~AnimationManager(){}

	bool Create(unsigned int );

	void ChangeAction(PLAYER_ACTION _action, bool _loop);

	CURRENT_STATE Update();

	void GetDrawingRect(D2D1_RECT_F& rect);

	void Enable(bool flag){
		isEnable = flag;
	}

private:
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;
	PLAYER_ACTION currentAction;
	unsigned int currentFrame;
	AnimationData animation;
	bool isEnable;
	bool loop;
};

#endif	// end of AnimationManager