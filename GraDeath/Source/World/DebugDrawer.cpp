#include "World/DebugDrawer.h"
#include "D2D/D2DGeometry.h"
#include "D2D/Brush/SolidBrush.h"

DefaultDebugDrawer::DefaultDebugDrawer(){
	brush = SolidBrush::Create(255, 255, 255, 255);
	this->AppendFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
}

DefaultDebugDrawer::~DefaultDebugDrawer(){
	brush->Release();
}

void DefaultDebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
	for (int i = 0; i < vertexCount; ++i){
		D3DXVECTOR2 _p1(vertices[i % vertexCount].x*32.0f, vertices[i % vertexCount].y*32.0f);
		D3DXVECTOR2 _p2(vertices[(i + 1) % vertexCount].x*32.0f, vertices[(i + 1) % vertexCount].y*32.0f);
		//Graphic::D2D::Geometry::DrawLine(brush, _p1.x, _p1.y, _p2.x, _p2.y);
	}
}

void DefaultDebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color){
	for (int i = 0; i < vertexCount; ++i){
		D3DXVECTOR2 _p1(vertices[i % vertexCount].x*32.0f, vertices[i % vertexCount].y*32.0f);
		D3DXVECTOR2 _p2(vertices[(i + 1) % vertexCount].x*32.0f, vertices[(i + 1) % vertexCount].y*32.0f);
		Graphic::D2D::Geometry::DrawLine(brush, _p1.x, _p1.y, _p2.x, _p2.y);
	}
}

void DefaultDebugDrawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
	b2Vec2 c(center.x*32.0f, center.y*32.0f);
	float rad = radius * 32.0f / 2.0f;
	Graphic::D2D::Geometry::DrawEllipse(brush, c.x, c.y, radius);
}

void DefaultDebugDrawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color){
	b2Vec2 c(center.x*32.0f, center.y*32.0f);
	float rad = radius * 32.0f / 2.0f;
	Graphic::D2D::Geometry::DrawEllipse(brush, c.x, c.y, rad);
}

void DefaultDebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
	b2Vec2 _p1(p1.x*32.0f, p1.y*32.0f);
	b2Vec2 _p2(p2.x*32.0f, p2.y*32.0f);
	Graphic::D2D::Geometry::DrawRect(brush, p1.x*32.0f, p1.y*32.0f, p2.x*32.0f, p2.y*32.0f);
}
