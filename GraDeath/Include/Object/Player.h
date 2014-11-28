#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include "Object/ObjectParameter.h"
#include <vector>
#include <memory>

#include "Object/CollisionShape.h"

using namespace std;

class Sprite;
struct ObjectParameter;
struct AnimetionParameter;
struct AnimationData;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName);
	void Release();

	void AddForce(b2Vec2& _force);

	void AttachFixture();
	void DettachFixture();

private:
	AnimationData animData;
	shared_ptr<Sprite> sprite;
	float hitPoint;
};

#endif	// end of Player