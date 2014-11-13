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
	void Release();

	void AddForce(b2Vec2& _force);

private:
	vector<vector<shared_ptr<Sprite>>> sprites;
	shared_ptr<ObjectParameter> parameter;
	float hitPoint;
};

#endif	// end of Player