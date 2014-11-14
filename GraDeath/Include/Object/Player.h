#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "Object/Object.h"
#include <vector>
#include <memory>

using namespace std;

class Sprite;
struct ObjectParameter;
struct AnimetionParameter;

class Player : public Object{
	friend class PlayerController;

public:
	Player();
	virtual ~Player();

	bool Init(const char* fileName);
	void Release();

	void AddForce(b2Vec2& _force);

private:
	void SetParameter ( ObjectParameter& _param );

	//void Set

	vector<vector<shared_ptr<Sprite>>> sprites;
	vector<shared_ptr<AnimetionParameter>> animeParameter;
	shared_ptr<Sprite> sprite;
	float hitPoint;
};

#endif	// end of Player