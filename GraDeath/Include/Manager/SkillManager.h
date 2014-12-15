#ifndef _SKIL_MANAGER_H_
#define _SKIL_MANAGER_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"

struct D3DXVECTOR2;

namespace SkillManager
{
	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type );

	void Update ();

	void Draw ();

	void SkillOn ( int _num, int _id, const D3DXVECTOR2 _pos );

	bool GetSkillUse ( int _num, SKILL_ID _id );

	float GetCoolTime ( int _num, SKILL_ID _id );

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num );

}

#endif