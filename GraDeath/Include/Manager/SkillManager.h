#ifndef _SKIL_MANAGER_H_
#define _SKIL_MANAGER_H_

#include "Object/Skill/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"

struct D3DXVECTOR2;
class  b2Body;

namespace SkillManager
{
	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type );

	void Update ();

	void Draw ();

	void Release ();

	void SkillOn ( int _num, int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg );

	bool GetSkillUse ( int _num, SKILL_ID _id );

	float GetCoolTime ( int _num, SKILL_ID _id );

	b2Body& Getb2Body ( int _num, SKILL_ID _id );

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num );

}

#endif