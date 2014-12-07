#ifndef _OBJECT_H__
#define _OBJECT_H__

#include <Box2D\Dynamics\b2Body.h>

class Object{
public:
	Object();
	virtual ~Object(){}

	const b2Vec2& GetPosition();

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetScale(float x, float y);
	void SetScaleX(float x);
	void SetScaleY(float y);

	void SetRotation(float _rot);

protected:
	b2Body* body;
};

#endif	// end of Object