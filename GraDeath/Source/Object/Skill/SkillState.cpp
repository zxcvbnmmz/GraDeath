#include "Object/Skill/SkillState.h"


void SkillState::Init ( CharacterInfo::PLAYER_TYPE _type )
{
	for ( int i = 0; i < SKILL_MAX; i++ )
	{
		time[ RECAST ][ i ] = .0f;// 180.0f + ( 180.0f * ( float )i );
		time[ COOLTIME ][ i ] = .0f;
	}
	type = _type;
}

void SkillState::Update ()
{
	for ( int i = 0; i < SKILL_MAX; i++ )
	{
		if ( time[ COOLTIME ][ i ] >= .0f )
		{
			time[ COOLTIME ][ i ] -= 1.f;
			if ( time[ COOLTIME ][ i ] <= .0f )
				time[ COOLTIME ][ i ] = .0f;
		}
	}
}

bool SkillState::GetUseSkill ( SKILL_ID _id )
{
	if ( ( time[ COOLTIME ][ _id ] == .0f ) )
	{
		time[ COOLTIME ][ _id ] = time[ RECAST ][ _id ];
		return true;
	}
	return false;
}

float SkillState::GetCoolTime ( SKILL_ID _id )
{
	return ( time[ COOLTIME ][ _id ] / time[ RECAST ][ _id ] );
}

CharacterInfo::PLAYER_TYPE SkillState::GetPlayerType ()
{
	return type;
}