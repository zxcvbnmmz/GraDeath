#include "Manager/SkillManager.h"
#include "Object/SkillState.h"

namespace SkillManager
{
	namespace
	{
		SkillState skill[ 4 ];
	}

	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type )
	{
		skill[ _num ].Init ( _type );
	}

	void Update ()
	{
		for ( int i = 0; i < 4; i++ )
		{
			skill[ i ].Update ();
		}
	}

	bool GetSkillUse ( int _num, SKILL_ID _id )
	{
		return skill[ _num ].GetUseSkill ( _id  );
	}

	float GetCoolTime ( int _num, SKILL_ID _id )
	{
		return skill[ _num ].GetCoolTime ( _id );
	}

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num )
	{
		return skill[ _num ].GetPlayerType ();
	}

}