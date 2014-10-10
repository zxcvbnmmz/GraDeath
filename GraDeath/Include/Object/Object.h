#ifndef _OBJECT_H__
#define _OBJECT_H__

#include <Box2D\Dynamics\b2Body.h>

class Object{
public:
	Object() :body(nullptr), pos(b2Vec2(0, 0)), scale(b2Vec2(1, 1)), rot(0){}
	virtual ~Object(){}

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetScale(float x, float y);
	void SetScaleX(float x);
	void SetScaleY(float y);

	void SetRotation(float _rot);
	void Move(float x, float y);

protected:
	b2Body* body;
	b2Vec2 pos;
	b2Vec2 scale;
	float rot;
};

#endif	// end of Object