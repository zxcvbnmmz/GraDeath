#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include "Object/ObjectParameter.h"
#include <vector>
#include <memory>

using namespace std;

class Sprite;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName, const b2Vec2& bodyPos);
	void Release();

	void AddForce(b2Vec2& _force);

	void AttachFixture(vector<shared_ptr<struct CollisionShape>>& shapes);

private:
	shared_ptr<Sprite> sprite;
};

#endif	// end of Player