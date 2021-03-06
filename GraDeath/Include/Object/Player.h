#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include "Object/ObjectParameter.h"
#include "CharacterController/CharacterInfo.h"
#include <vector>
#include <memory>
#include "D2D/Sprite/Sprite.h"

using namespace std;

class Sprite;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName, const b2Vec2& bodyPos, float scale);
	void Release();
	class b2Body* GetBody(){
		return body;
	}

	void AddForce(b2Vec2& _force);
	void AddPosition(float x, float y);
	void SetPosition(float x, float y);
	void SetAngularVelocity(b2Vec2& _force);

	void AttachFixture(vector<shared_ptr<struct CollisionShape>>& shapes);
	void SetPlayerType(CharacterInfo::PLAYER_TYPE _type){
		playerType = _type;
	}

	CharacterInfo::PLAYER_TYPE GetPlayerType(){
		return playerType;
	}

	void Destroy();
	bool IsCollidable;

private:
	shared_ptr<Sprite> sprite;
	CharacterInfo::PLAYER_TYPE playerType;
};

#endif	// end of Player