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
	int width = 0;
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
	std::shared_ptr<b2Shape> reverseShape;
	b2Fixture* fixture = nullptr;
	b2Filter filter;
	int strength;
	int width;

public:
	CollisionShape(CircleDef& def){
		b2CircleShape* _shape = new b2CircleShape;
		_shape->m_p.x = (float)def.x / 32.0f;
		_shape->m_p.y = (float)def.y / 32.0f;
		_shape->m_radius = (float)def.r / 32.0f;

		shape.reset(_shape);

		b2CircleShape* _reverseShape = new b2CircleShape;
		_reverseShape->m_p.x = (def.width / 32) - (float)def.x / 32.0f;
		//_reverseShape->m_p.y = (def.height / 32) - (float)def.y / 32.0f;
		_reverseShape->m_radius = (float)def.r / 32.0f;

		reverseShape.reset(_reverseShape);

		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		width = def.width/32;
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

		b2PolygonShape* _reverseShape = new b2PolygonShape;

		for (int i = 0; i < 4; ++i){
			// 代入の際に、単位変換の為に32.0fで割る必要あり
			pos[i].x = (def.width / 32) - (float)def.x[i] / 32.0f;
		}
		_reverseShape->Set(pos, 4);
		shape.reset(_reverseShape);

		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		width = def.width / 32;
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

	int GetStrength(){
		return strength;
	}

	void DestoryFixture(b2Body* body){
		if (fixture != nullptr){
			body->DestroyFixture(fixture);
		}
	} 

	void Reverse(bool reverse){
		b2Shape::Type type = shape->GetType();
		if (type == b2Shape::e_circle){
			b2CircleShape* circle = reinterpret_cast<b2CircleShape*>(shape.get());
		}
		else if (type == b2Shape::e_polygon){
			b2PolygonShape* polygon = reinterpret_cast<b2PolygonShape*>(shape.get());
			for (int i = 0; i < 4; ++i)
				polygon->m_vertices[i] =  b2Vec2(width - polygon->m_vertices[i].x, polygon->m_vertices[i].y);
		}
			
	}
};

#endif	// end of CollisionShape


