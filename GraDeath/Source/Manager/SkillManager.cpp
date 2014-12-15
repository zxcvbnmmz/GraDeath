#include "Manager/SkillManager.h"
#include "Object/SkillState.h"
#include "Object/Skill.h"

namespace SkillManager
{
	namespace
	{
		SkillState skillState[ 4 ];
		Skill skill[4];
	}

	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type )
	{
		skillState[ _num ].Init ( _type );

		skill[ _num ].Init ("Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin");
	}

	void Update ()
	{
		for ( int i = 0; i < 4; i++ )
		{
			skillState[ i ].Update ();
			skill[ i ].Update ();
		}
	}

	void Draw ()
	{
		for ( int i = 0; i < 4; i++ )
		{
			skill[ i ].Draw();
		}
	}

	void SkillOn ( int _num, int _id, const D3DXVECTOR2 _pos )
	{
		skill[ _num ].SetPosition ( _pos );
		skill[ _num ].SkillOn ();
	}

	bool GetSkillUse ( int _num, SKILL_ID _id )
	{
		return skillState[ _num ].GetUseSkill ( _id );
	}

	float GetCoolTime ( int _num, SKILL_ID _id )
	{
		return skillState[ _num ].GetCoolTime ( _id );
	}

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num )
	{
		return skillState[ _num ].GetPlayerType ();
	}

}