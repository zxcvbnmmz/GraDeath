#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include <vector>
#include <memory>

using namespace std;

class Sprite;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName);

private:
	vector<vector<shared_ptr<Sprite>>> sprites;
};

#endif	// end of Player