#include "World/World.h"
#include <Box2D\Box2D.h>

#include "D2D/Brush/SolidBrush.h"
#include "D2D/D2DGeometry.h"

static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

namespace{
	b2World world(b2Vec2(0.0f, 9.8f));
}

class b2DebugDraw : public b2Draw{
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
		if (vertexCount == 4){
			b2Vec2 _p1(vertices[0].x*32.0f, vertices[0].y*32.0f);
			b2Vec2 _p2(vertices[2].x*32.0f, vertices[2].y*32.0f);
			Graphic::D2D::Geometry::DrawRect(brush, _p1.x, _p1.y, _p2.x, _p2.y);
		}
	}

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
		if (vertexCount == 4){
			b2Vec2 _p1(vertices[0].x*32.0f, vertices[0].y*32.0f);
			b2Vec2 _p2(vertices[2].x*32.0f, vertices[2].y*32.0f);
			Graphic::D2D::Geometry::DrawRect(brush, _p1.x, _p1.y, _p2.x, _p2.y);
		}
	}

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
		b2Vec2 c(center.x*32.0f, center.y*32.0f);
		Graphic::D2D::Geometry::DrawEllipse(brush, c.x, c.y, radius);
	}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){
		b2Vec2 c(center.x*32.0f, center.y*32.0f);
		float rad = radius * 32.0f;
		Graphic::D2D::Geometry::DrawEllipse(brush, c.x, c.y, rad);
	}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
		b2Vec2 _p1(p1.x*32.0f, p1.y*32.0f);
		b2Vec2 _p2(p2.x*32.0f, p2.y*32.0f);
		Graphic::D2D::Geometry::DrawRect(brush, p1.x*32.0f, p1.y*32.0f, p2.x*32.0f, p2.y*32.0f);
	}
	void DrawTransform(const b2Transform& xf){}

	SolidBrush* brush = SolidBrush::Create(255, 255, 255, 255);

public:
	~b2DebugDraw(){
		if (brush){
			brush->Release();
		}
	}
};

std::shared_ptr<b2DebugDraw> d;

b2Body* World::CreateBody(const b2BodyDef* def){
	if (d == nullptr){
		d.reset(new b2DebugDraw);
		d->SetFlags(b2Draw::e_aabbBit | b2Draw::e_shapeBit);
	}

	return world.CreateBody(def);
}

b2Joint* World::CreateJoint(const b2JointDef* def){
	return world.CreateJoint(def);
}

void World::DestoryBody(b2Body* _body){
	world.DestroyBody(_body);
}

void World::DestoryJoint(b2Joint* _joint){
	world.DestroyJoint(_joint);
}

int World::GetBodyCount(){
	return world.GetBodyCount();
}

b2Body* World::GetBodyList(){
	return world.GetBodyList();
}

int World::GetContactCount(){
	return world.GetContactCount();
}

b2Contact* World::GetContactList(){
	return world.GetContactList();
}

void World::Step(float timeStep){
	world.Step(timeStep,velocityIterations,positionIterations);
}

void World::DrawDebugData(b2Draw* drawer){
	b2DebugDraw* temp = d.get();
	world.SetDebugDraw(temp);
	world.DrawDebugData();
}

