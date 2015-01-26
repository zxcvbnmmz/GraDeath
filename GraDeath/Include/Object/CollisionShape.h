#ifndef _COLLISION_SHAPE_H__
#define _COLLISION_SHAPE_H__

#include <Box2D\Box2D.h>
#include "Object/ObjectMask.h"

struct CollisionDef{ 
	virtual ~CollisionDef(){} 
	int strength = 0;
	int categoryBit = 0x0002;
	int maskBit = 0x0003;
	int groupIndex = -1;
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
	b2Fixture* fixture = nullptr;
	b2Filter filter;
	int strength;

public:
	CollisionShape(CircleDef& def){
		b2CircleShape* _shape = new b2CircleShape;
		_shape->m_p.x = (float)def.x / 32.0f; 
		_shape->m_p.y = (float)def.y / 32.0f;
		_shape->m_radius = (float)def.r / 32.0f;
		 
		shape.reset(_shape);
		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		strength = def.strength;
	}

	CollisionShape(SquareDef& def){
		b2PolygonShape* _shape = new b2PolygonShape;
		b2Vec2 pos[4];

		for (int i = 0; i < 4; ++i){
			// 代入の際に、単位変換の為に32.0fで割る必要あり
			pos[i].x = (float)def.x[i] / 32.0f;
			pos[i].y = (float)def.y[i] / 32.0f;
		}
		_shape->Set(pos, 4);
		shape.reset(_shape);

		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		this->strength = def.strength;
	}

	void AddFixture(b2Body* body){
		b2FixtureDef def;
		def.shape = shape.get();
		def.filter = filter;
		def.density = 0.0f;

		// 摩擦係数の設定
		// ステージが不完全なので、ここで多めに設定しておく
		def.friction = 20.0f;
		def.userData = this;
		body->CreateFixture(&def);
	}

	b2Body* GetBody(){
		return fixture->GetBody();
	}

	void DestoryFixture(b2Body* body){
		if (fixture != nullptr){
			body->DestroyFixture(fixture);
		}
	} 
	float GetStrength(){
		return strength;
	}
};

#endif	// end of CollisionShape


