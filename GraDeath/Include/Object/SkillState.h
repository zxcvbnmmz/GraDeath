#ifndef _SKILL_STATE_H_
#define _SKILL_STATE_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"

class SkillState
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
	SkillState (){}

	~SkillState (){}

	void Init ( CharacterInfo::PLAYER_TYPE _type );

	void Update ();

	bool GetUseSkill ( SKILL_ID _id );

	float GetCoolTime ( SKILL_ID _id );

	CharacterInfo::PLAYER_TYPE GetPlayerType ();

};

#endif