#include "Object/Skill/WhiteBlackSkill.h"
#include <Box2D\Dynamics\b2Body.h>
#include "Loader/PlayerLoader.h"
#include "Object/Skill/Skill.h"
#include "World/World.h"


D3DXVECTOR2 setPosition[2][3] =
{
	{
		D3DXVECTOR2 ( 150, -215.0f ),
		D3DXVECTOR2 ( 150, -365.0f ),
		D3DXVECTOR2 ( 30, -350.0f )
	},
	{
		D3DXVECTOR2 ( -400, -215.0f ),
		D3DXVECTOR2 ( -800, -365.0f ),
		D3DXVECTOR2 ( -700, -350.0f )
	},
};


WhiteBlackSkill::~WhiteBlackSkill ()
{
	int size = skills.size ();
	for ( int i = 0; i < size; i++ )
	{
		if ( skills[i] != nullptr )
		{
			delete skills[i];
			skills[i] = nullptr;
		}
	}
	skills.clear ();

	World::DestoryBody ( body );
}

void WhiteBlackSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/skill01.png", SKILL_ID_LOAD::SKILL_ID_BLACKWHITE );
	skills.push_back ( first );

	Skill* second = new Skill;
	second->Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_Skill_Second.bin", L"Resource/Object/Skill/WhiteBlack/shirokuro_Skill_Second.png", SKILL_ID_LOAD::SKILL_ID_BLACKWHITE );
	skills.push_back ( second );

	Skill* third = new Skill;
	third->Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_Skill_Third.bin", L"Resource/Object/Skill/WhiteBlack/shirokuro_Skill_Third.png", SKILL_ID_LOAD::SKILL_ID_BLACKWHITE );
	skills.push_back ( third );

	SkillSet::Initb2Body ();
}

void WhiteBlackSkill::Update ()
{
	for ( auto& skill : skills )
	{
		skill->Update ( body );
	}
}

void WhiteBlackSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void WhiteBlackSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	if ( _id >= skills.size () )
		return

	SkillSetDettachFixture ( body );

	int dir = dirFlg - ( -3 * dirFlg ) + 1;
	D3DXVECTOR2 temp = ( _pos * 32.0f );//*( -1.0f*dirFlg )
	//D3DXVECTOR2 temp2 = D3DXVECTOR2 ( setPosition[ dirFlg ][ _id ].x*( -1.0f*dirFlg ), setPosition[ _id ].y );
	skills[ _id ]->SetPosition ( ( temp + setPosition[ dirFlg ][ _id ] ), dirFlg );
	skills[ _id ]->SkillOn ();
	temp = skills[ _id ]->GetPosition ();
	body->SetTransform ( b2Vec2 ( temp.x / 32.0f, temp.y / 32.0f ), 0 );
	skills[_id]->SetAttachFixture ( body );
}

b2Body* WhiteBlackSkill::Getb2Body ()
{
	for ( auto& skill : skills )
	{
		if ( skill->IsActive () )
		{
			return body;
		}
	}
	return nullptr;
	//return skills[ _num ]->Getb2Body ();
}