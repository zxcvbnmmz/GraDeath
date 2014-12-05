#include "Object/Skill.h"


void Skill::Init ()
{
	for ( int i = 0; i < SKILL_MAX; i++ )
	{
		time[ RECAST ][ i ] = 180.0f + ( 180.0f * ( float )i );
		time[ COOLTIME ][ i ] = .0f;
	}
}

void Skill::Update ()
{
	for ( int i = 0; i < SKILL_MAX; i++ )
	{
		if ( time[ COOLTIME ][ i ] >= .0f )
		{
			time[ COOLTIME ][ i ] -= .0f;
			if ( time[ COOLTIME ][ i ] <= .0f )
				time[ COOLTIME ][ i ] = .0f;
		}
	}
}

bool Skill::GetUseSkill ( SKILL_ID _id )
{
	return ( time[ COOLTIME ][ _id ] == .0f ) ? true : false;
}

float Skill::GetCoolTime ( SKILL_ID _id )
{
	return time[ COOLTIME ][ _id ];
}