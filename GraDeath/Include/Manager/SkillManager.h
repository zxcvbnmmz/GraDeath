#ifndef _SKIL_MANAGER_H_
#define _SKIL_MANAGER_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"


namespace SkillManager
{
	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type );

	void Update ();

	bool GetSkillUse ( int _num, SKILL_ID _id );

	float GetCoolTime ( int _num, SKILL_ID _id );

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num );

}

#endif