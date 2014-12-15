#ifndef _COLLISION_SHAPE_H__
#define _COLLISION_SHAPE_H__

#include <Box2D\Box2D.h>
#include "Object/ObjectMask.h"

struct CollisionDef{ 
	virtual ~CollisionDef(){} 
	int strength;
	int categoryBit;
	int maskBit;
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
		//filter.categoryBits = def.mask;
		//filter.maskBits = def.mask;
		strength = def.strength;
	}

	CollisionShape(SquareDef& def){
		b2PolygonShape* _shape = new b2PolygonShape;
		b2Vec2 pos[4];

		for (int i = 0; i < 4; ++i){
			// ����̍ۂɁA�P�ʕϊ��ׂ̈�32.0f�Ŋ���K�v����
			pos[i].x = (float)def.x[i] / 32.0f;
			pos[i].y = (float)def.y[i] / 32.0f;
		}
		_shape->Set(pos, 4);
		shape.reset(_shape);

		//filter.maskBits = def.mask;
		this->strength = def.strength;
	}

	void AddFixture(b2Body* body){
		fixture = body->CreateFixture(shape.get(),0);
		// ���C�W���̐ݒ�
		// �X�e�[�W���s���S�Ȃ̂ŁA�����ő��߂ɐݒ肵�Ă���
		fixture->SetFriction(20.0f);
		
		// �����W��
		//fixture->SetRestitution(0);

		fixture->SetFilterData(filter);
	}

	b2Body* GetBody(){
		return fixture->GetBody();
	}

	void DestoryFixture(b2Body* body){
		if (fixture != nullptr){
			body->DestroyFixture(fixture);
		}
	} 
};

#endif	// end of CollisionShape


