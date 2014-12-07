#ifndef _SKILL_H_
#define _SKILL_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"

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
	CharacterInfo::PLAYER_TYPE type;

public:
	Skill (){}

	~Skill (){}

	void Init ( CharacterInfo::PLAYER_TYPE _type );

	void Update ();

	bool GetUseSkill ( SKILL_ID _id );

	float GetCoolTime ( SKILL_ID _id );

	CharacterInfo::PLAYER_TYPE GetPlayerType ();

};

#endif