#include "Object/CollisionShape.h"

CollisionDef::CollisionDef(){
	strength = 0;
	categoryBit = 0x0002;
	maskBit = 0x0003;
	groupIndex = 1;
	width = 0, height = 0;
	scale = 1;
}

CollisionDef::~CollisionDef(){}

CollisionShape::CollisionShape(CircleDef& def){
	b2CircleShape* _shape = new b2CircleShape;
	width = def.width / 32.0f;
	height = def.height / 32.0f;
	scale = def.scale;

	_shape->m_p.x = (float)def.x / 32.0f + ((width - (width * scale)) / 2.0f);
	_shape->m_p.y = (float)def.y / 32.0f + ((height - (height * scale)) / 2.0f);
	_shape->m_radius = (float)def.r / 32.0f;

	shapeData.circle.x = (float)def.x / 32.0f * scale + ((width - (width * scale)) / 2.0f);
	shapeData.circle.y = (float)def.y / 32.0f * scale + ((height - (height * scale)) / 2.0f);
	shapeData.circle.rad = (float)def.r / 32.0f;

	shape.reset(_shape);

	filter.categoryBits = def.categoryBit;
	filter.maskBits = def.maskBit;
	filter.groupIndex = def.groupIndex;
	strength = def.strength;	
}

CollisionShape::CollisionShape(SquareDef& def){
	b2PolygonShape* _shape = new b2PolygonShape;
	b2Vec2 pos[4];
	width = def.width / 32.0f;
	height = def.height / 32.0f;
	scale = def.scale;

	for (int i = 0; i < 4; ++i){
		// 代入の際に、単位変換の為に32.0fで割る必要あり
		pos[i].x = (float)def.x[i] / 32.0f + ((width - (width * scale)) / 2.0f);
		pos[i].y = (float)def.y[i] / 32.0f + ((height - (height * scale)) / 2.0f);

		shapeData.polygon.x[i] = ((float)def.x[i] / 32.0f) * scale + ((width - (width * scale)) / 2.0f);
		shapeData.polygon.y[i] = ((float)def.y[i] / 32.0f) * scale + ((height - (height * scale)) / 2.0f);
	}
	_shape->Set(pos, 4);
	shape.reset(_shape);

	filter.categoryBits = def.categoryBit;
	filter.maskBits = def.maskBit;
	filter.groupIndex = def.groupIndex;
	this->strength = def.strength;
}

void CollisionShape::AddFixture(b2Body* body){
	b2FixtureDef def;
	if (shape->GetType() == b2Shape::e_polygon){
		b2PolygonShape* poly = reinterpret_cast<b2PolygonShape*>(shape.get());
		b2Vec2 pos[4];
		for (int i = 0; i < 4; ++i){
			pos[i] = b2Vec2(shapeData.polygon.x[i], shapeData.polygon.y[i]);
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

void CollisionShape::Reverse(){
	b2Shape* shape = fixture->GetShape();
	if (!shape){
		return;
	}
	b2Shape::Type type = shape->GetType();
	if (type == b2Shape::e_circle){
		b2CircleShape* circle = reinterpret_cast<b2CircleShape*>(shape);
		circle->m_p = b2Vec2(width - shapeData.circle.x, shapeData.circle.y);
	}
	else if (type == b2Shape::e_polygon){
		b2PolygonShape* polygon = reinterpret_cast<b2PolygonShape*>(shape);
		for (int i = 0; i < 4; ++i){
			polygon->m_vertices[i].x = width - shapeData.polygon.x[i];
		}
		b2Vec2 pos[4];
		for (int i = 0; i < 4; ++i){
			pos[i] = b2Vec2(width - shapeData.polygon.x[i], shapeData.polygon.y[i]);
		}
		polygon->Set(pos, 4);
	}
}
