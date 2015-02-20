#include "Manager/SkillManager.h"
#include "Object/Skill/SkillState.h"
#include "Object/Skill/Skill.h"
#include <vector>
#include "Object/Skill/SkillSet.h"
#include "Object/Skill/WhiteBlackSkill.h"
#include "Object/Skill/RedSkill.h"
#include "Object/Skill/BlueSkill.h"
#include "Object/Skill/YellowSkill.h"


namespace SkillManager
{
	namespace
	{
		SkillState skillState[ 4 ];
		Skill skill[4];
		std::vector<SkillSet*> skillset;
	}

	SkillSet* CreateSkillSet ( CharacterInfo::PLAYER_TYPE _type )
	{
		switch ( _type )
		{
		case CharacterInfo::PLAYER_RED:
			new RedSkill;
			break;

		case CharacterInfo::PLAYER_BLUE:
			new BlueSkill;
			break;

		case CharacterInfo::PLAYER_YELLOW:
			new YellowSkill;
			break;

		case CharacterInfo::PLAYER_GRAY:
			new WhiteBlackSkill;
			break;

		case CharacterInfo::PLAYER_RONDOM:
			return nullptr;
			break;

		case CharacterInfo::PLAYER_NON:
			return nullptr;
			break;

		default:
			break;
		}
		return nullptr;
	}

	void Init ( int _num, CharacterInfo::PLAYER_TYPE _type )
	{
		skillState[ _num ].Init ( _type );

		SkillSet* tempSkill = new WhiteBlackSkill; //CreateSkillSet ( _type );// new WhiteBlackSkill;
		tempSkill->Init ();
		skillset.push_back ( tempSkill );

		//skill[ _num ].Init ("Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/" );
	}

	void Update ()
	{
		for ( int i = 0; i < 4; i++ )
		{
			skillState[ i ].Update ();
			skillset[ i ]->Update ();
			//skill[ i ].Update ();
		}
	}

	void Draw ()
	{
		for ( int i = 0; i < 4; i++ )
		{
			skillset[ i ]->Draw ();
			//skill[ i ].Draw();
		}
	}

	void Release ()
	{
		int size = skillset.size ();
		for ( int i = 0; i < size; i++ )
		{
			if ( skillset[i] != nullptr )
			{
				delete skillset[ i ];
				skillset[ i ] = nullptr;
			}
		}
		skillset.clear ();
	}

	void SkillOn ( int _num, int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
	{
		skillset[ _num ]->SetPosition ( _id, _pos, dirFlg );
		//skill[ _num ].SetPosition ( _pos );
		//skill[ _num ].SkillOn ();
	}

	bool GetSkillUse ( int _num, SKILL_ID _id )
	{
		return skillState[ _num ].GetUseSkill ( _id );
	}

	float GetCoolTime ( int _num, SKILL_ID _id )
	{
		return skillState[ _num ].GetCoolTime ( _id );
	}

	b2Body* Getb2Body ( int _num )
	{
		return skillset[ _num ]->Getb2Body ();
	}

	CharacterInfo::PLAYER_TYPE GetPlayerType ( int _num )
	{
		return skillState[ _num ].GetPlayerType ();
	}

}