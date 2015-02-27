#ifndef _SKILL_SET_H_
#define _SKILL_SET_H_

#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Box2D.h>
#include <vector>
#include "World/World.h"

class Skill;
struct AnimationData;
struct D3DXVECTOR2;
class b2Body;

class SkillSet
{
protected:
	std::vector< Skill* > skills;
	b2Body* body = nullptr;

public:
	SkillSet (){}

	virtual ~SkillSet (){}

	virtual void Init () = 0;

	virtual void Update () = 0;

	virtual void Draw () = 0;

	virtual bool SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg ) = 0;
	virtual bool IsActive () = 0;

	virtual b2Body* Getb2Body () = 0;

	void Initb2Body ()
	{
		b2BodyDef def;
		def.position = b2Vec2 ( 0, 0 );
		def.type = b2_staticBody;

		body = World::CreateBody ( &def );
		body->SetUserData ( this );
	}

	void SkillSetDettachFixture ( b2Body* body )
	{
		b2Fixture* fixture = body->GetFixtureList ();
		if ( fixture == nullptr ){
			return;
		}

		while ( fixture != nullptr ){
			b2Fixture* temp = fixture->GetNext ();
			body->DestroyFixture ( fixture );
			fixture = temp;
		}
	}

};

#endif
