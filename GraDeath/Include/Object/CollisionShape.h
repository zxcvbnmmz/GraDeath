#ifndef _COLLISION_SHAPE_H__
#define _COLLISION_SHAPE_H__

#include <Box2D\Box2D.h>
#include "Object/ObjectMask.h"

struct CollisionDef{ 
	CollisionDef();
	virtual ~CollisionDef();

	int strength;
	int categoryBit;
	int maskBit;
	int groupIndex;
	float width, height;
	float scale;
};

struct CircleDef:public CollisionDef{
	int x, y;
	int r;
};

struct SquareDef:public CollisionDef{
	int x[4], y[4];
	int w, h;
};

struct CollisionShape{
private:
	std::shared_ptr<b2Shape> shape;
	union {
		struct { float x[4], y[4]; }polygon;
		struct { float x, y, rad; }circle;
	}shapeData;

	b2Fixture* fixture = nullptr;
	b2Filter filter;
	int strength;
	float width,height;
	float scale;

public:
	CollisionShape(CircleDef& def);

	CollisionShape(SquareDef& def);

	void AddFixture(b2Body* body);

	b2Body* GetBody(){
		return fixture->GetBody();
	}

	int GetStrength(){
		return strength;
	}

	void DestoryFixture(b2Body* body){
		if (fixture != nullptr){
			body->DestroyFixture(fixture);
		}
	} 

	void Reverse();
};

#endif	// end of CollisionShape


