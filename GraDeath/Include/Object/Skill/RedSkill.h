#ifndef _RED_SKILL_H_
#define _RED_SKILL_H_

#include "Object/Skill/SkillSet.h"

struct D3DXVECTOR2;

class RedSkill : public SkillSet
{
public:
	RedSkill (){}

	~RedSkill ();

	void Init ();

	void Update ();

	void Draw ();

	void SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg );

	b2Body* Getb2Body ();

};

#endif