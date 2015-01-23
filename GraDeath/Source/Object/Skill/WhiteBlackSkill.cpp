#include "Object/Skill/WhiteBlackSkill.h"
#include "Object/Skill/WhiteBlackFirstSkill.h"
#include "Object/Skill/WhiteBlackSecond.h"
#include "Loader/PlayerLoader.h"

D3DXVECTOR2 setPosition[] =
{
	D3DXVECTOR2 ( 0, -290.0f ),
	D3DXVECTOR2 ( -400, -400.0f ),
	D3DXVECTOR2 ( -100, -290.0f )
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
}

void WhiteBlackSkill::Init ()
{
	Skill* first = new Skill;
	first->Init ( "Resource/Object/Skill/WhiteBlack/shirokuro_skill01.bin", L"Resource/Object/Skill/WhiteBlack/skill01.png", SKILL_ID_LOAD::SKILL_ID_BLACKWHITE );
	skills.push_back ( first );

	//WhiteBlackSecond* second = new WhiteBlackSecond;
	//second->Init ( "", L"" );
	//skills.push_back ( second );

	Skill* third = new Skill;
	third->Init ( "Resource/Object/Skill/Blue/Blue_Skill_Third3.bin", L"Resource/Object/Skill/Blue/Blue_Skill_Third3.png", SKILL_ID_LOAD::SKILL_ID_BLUE );
	//third->SetSize ( D3DXVECTOR2 ( 600, 600 ));
	skills.push_back ( third );
}

void WhiteBlackSkill::Update ()
{
	for ( auto& skill : skills )
		skill->Update ();
}

void WhiteBlackSkill::Draw ()
{
	for ( auto& skill : skills )
		skill->Draw ();
}

void WhiteBlackSkill::SetPosition ( int _id, const D3DXVECTOR2 _pos, unsigned int dirFlg )
{
	D3DXVECTOR2 temp = ( _pos * 32.0f );
	skills[ _id ]->SetPosition ( temp + setPosition[ _id ], dirFlg );
	skills[ _id ]->SkillOn ();
}

AnimationData& WhiteBlackSkill::GetAnimationData ( int _num )
{
	return skills[ _num ]->GetAnimationData ();
}