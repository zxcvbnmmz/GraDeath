#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

private:
	class Sprite* sprite;
};

#endif	// end of Player