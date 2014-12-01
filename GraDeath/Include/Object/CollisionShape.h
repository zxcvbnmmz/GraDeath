#ifndef _COLLISION_SHAPE_H__
#define _COLLISION_SHAPE_H__

#include <Box2D\Box2D.h>

struct CollisionDef{ virtual ~CollisionDef(){} };

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
	b2Fixture* fixture;

public:
	CollisionShape(CircleDef& def){
		b2CircleShape* _shape = new b2CircleShape;
		_shape->m_p.x = (float)def.x;
		_shape->m_p.y = (float)def.y;
		_shape->m_radius = (float)def.r;

		shape.reset(_shape);
	}

	CollisionShape(SquareDef& def){
		b2PolygonShape* _shape = new b2PolygonShape;
		b2Vec2 pos[4];

		for (int i = 0; i < 4; ++i){
			// 多分代入の際に、単位変換の為に32.0fで割るか掛ける必要あり
			pos[i].x = (float)def.x[i]/32.0f;
			pos[i].y = (float)def.y[i]/32.0f;
		}
		_shape->Set(pos, 4);
	}

	void AddFixture(b2Body* body){
		fixture = body->CreateFixture(shape.get(),0);
	}

	b2Body* GetBody(){
		return fixture->GetBody();
	}

	void DestoryFixture(b2Body* body){
		body->DestroyFixture(fixture);
	}
};

#endif	// end of CollisionShape



