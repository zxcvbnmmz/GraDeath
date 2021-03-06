#ifndef _YELLOW_SKILL_H_
#define _YELLOW_SKILL_H_

#include "Object/Skill/SkillSet.h"

struct D3DXVECTOR2;

class YellowSkill : public SkillSet
{
public:
	YellowSkill (){}

	~YellowSkill ();

	void Init ();

	void Update ();

	void Draw ();

	bool SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg );

	bool IsActive ();

	b2Body* Getb2Body ();

};

#endif