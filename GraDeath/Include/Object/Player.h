#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include <vector>
#include <memory>

using namespace std;

class Sprite;
struct ObjectParameter;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName);

private:
	vector<vector<shared_ptr<Sprite>>> sprites;
	shared_ptr<ObjectParameter> parameter;
};

#endif	// end of Player