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
	float width = 0, height = 0;
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
	CollisionShape(CircleDef& def){	
		b2CircleShape* _shape = new b2CircleShape;
		width = def.width / 32.0f;
		height = def.height / 32.0f;
		scale = def.scale;
		
		_shape->m_p.x = (float)def.x / 32.0f + ((width - (width * scale)) / 2);
		_shape->m_p.y = (float)def.y / 32.0f + ((height - (height * scale)) / 2);
		_shape->m_radius = (float)def.r / 32.0f;

		shapeData.circle.x = (float)def.x / 32.0f + ((width - (width * scale)) / 2);
		shapeData.circle.y = (float)def.y / 32.0f + ((height - (height * scale)) / 2);
		shapeData.circle.rad = (float)def.r / 32.0f;

		shape.reset(_shape);

		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		strength = def.strength;
	}

	CollisionShape(SquareDef& def){
		b2PolygonShape* _shape = new b2PolygonShape;
		b2Vec2 pos[4];
		width = def.width / 32.0f;
		height = def.height / 32.0f;
		scale = def.scale;

		for (int i = 0; i < 4; ++i){
			// 代入の際に、単位変換の為に32.0fで割る必要あり
			pos[i].x = (float)def.x[i] / 32.0f + ((width - (width * scale)) / 2.0f);
			pos[i].y = (float)def.y[i] / 32.0f + ((height - (height * scale)) / 2.0f);

			shapeData.polygon.x[i] = ((float)def.x[i] / 32.0f);
			shapeData.polygon.y[i] = ((float)def.y[i] / 32.0f);
		}
		_shape->Set(pos, 4);
		shape.reset(_shape);

		filter.categoryBits = def.categoryBit;
		filter.maskBits = def.maskBit;
		filter.groupIndex = def.groupIndex;
		width = def.width / 32.0f;
		this->strength = def.strength;
	}

	void AddFixture(b2Body* body){
		b2FixtureDef def;
		if (shape->GetType() == b2Shape::e_polygon){
			b2PolygonShape* poly = reinterpret_cast<b2PolygonShape*>(shape.get());
			b2Vec2 pos[4];
			for (int i = 0; i < 4; ++i){
				pos[i] = b2Vec2(shapeData.polygon.x[i] * scale + ((width - (width * scale)) / 2.0f), shapeData.polygon.y[i] * scale + ((height - (height * scale)) / 2.0f));
			}
			//poly->m_vertices[i].x = shapeData.polygon.x[i] * scale + ((width - (width * scale)) / 2.0f);
			//poly->m_vertices[i].y = shapeData.polygon.y[i] * scale + ((height - (height * scale)) / 2.0f);
			poly->Set(pos, 4);
		}
		else{
			b2CircleShape* circle = reinterpret_cast<b2CircleShape*>(shape.get());
			circle->m_p = b2Vec2(shapeData.circle.x, shapeData.circle.y);
			circle->m_radius = shapeData.circle.rad;
		}

		def.shape = shape.get();
		def.filter = filter;
		def.density = 0.0f;

		// 摩擦係数の設定
		// ステージが不完全なので、ここで多めに設定しておく
		def.friction = 20.0f;
		def.userData = this;
		fixture = body->CreateFixture(&def);
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

	void Reverse(){
		b2Shape* shape = fixture->GetShape();
		if (!shape){
			return;
		}
		b2Shape::Type type = shape->GetType();
		if (type == b2Shape::e_circle){
			b2CircleShape* circle = reinterpret_cast<b2CircleShape*>(shape);
			circle->m_p.x = (width * scale) - circle->m_p.x;
		}
		else if (type == b2Shape::e_polygon){
			b2PolygonShape* polygon = reinterpret_cast<b2PolygonShape*>(shape);
			for (int i = 0; i < 4; ++i){
				polygon->m_vertices[i].x = (width * scale) - polygon->m_vertices[i].x;
			}
		}
	}
};

#endif	// end of CollisionShape


