#ifndef _SKILL_H_
#define _SKILL_H_

#include "Object/SkillDefine.h"

class Skill
{
private:
	enum
	{
		RECAST = 0,
		COOLTIME = 1,
		CAST_MAX,
	};
	float time[ CAST_MAX ][ SKILL_MAX ];

public:
	Skill (){}

	~Skill (){}

	void Init ();

	void Update ();

	bool GetUseSkill ( SKILL_ID _id );

	float GetCoolTime ( SKILL_ID _id );

};

#endif